#include "dbfete.h"
#include "type.h"
#include "../utils/tool.hpp"
#include "../model/modelmanager.h"

#include <set>
#include <algorithm>
#include <sstream>
#include <unistd.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

DBFETE::DBFETE():
    dest_num(0),
    origin_num(0),
    readygo_num(0){

    Finished = false;
}

DBFETE::DBFETE(const Config &config){ 
    this->_config = config;
    this->Finished = false;
}

DBFETE& DBFETE::operator=(const DBFETE& fete){
    //暂未处理
}


/**********************************/


void DBFETE::loadNetwork(){
    //加载links和nodes
    loadLinks(links, paths);
    loadNodes(nodes);

	//建立link的前后关系
	fillLinks(paths,links);

    //处理起终点
    for(auto path:paths){
        startIds.insert(path.front());
        endIds.insert(path.back());
    }

	//测试信息
	for(auto link:links){
		LOG_DEBUG(my2string("link",link.first, " previous id num is " ,link.second->pids.size()));
	}

	//初始化每个起点的需求
	for(auto sid: startIds)
		pcurnum[sid] = 0;
	
}

void DBFETE::init(){
    //加载路网
    LOG_TRACE("init fete ...");
    loadNetwork();
    //TODO params for generate source inflow, add to config later.
    curtime = 0;
    curnum = 0;
    car_num = 0; //当前已经生成的车辆数目
    readygo_num = 0;

    total_num = 500;
    min_num = 60;
    max_num = 1800;
    mean_num = max_num/3.0 + 2.0 * min_num / 3.0; //640
    genAgentNumMax = 2.0 * total_num / (max_num - min_num); //14.367816

    genCount = 0; //表示已经生成的累计的车数,小数部分可以累计到下一次生成中，而不能直接舍弃


    //get modelmanager
    shared_ptr<ModelManager> model_manager = ModelManager::getModelManager();
    model_manager->init(_config);

    //load model for each node and link
    for(auto mnode : nodes){
        int node_id = mnode.first;
        node_models[node_id] = model_manager->getXGBoostModelByNode(node_id);
    }

    for(auto mlink : links){
        int link_id = mlink.first;
        link_models[link_id] = model_manager->getXGBoostModelByLink(link_id);
    }


    origin_num = total_num;
    dest_num = 0;
    
}

Config DBFETE::getConfig(){
    return _config;
}

vector<vector<int>> DBFETE::getPaths(){
    return paths;
}

void DBFETE::generate(){
    //TODO 需要累计存储，而不是全部发车出去。
    int frames = _config.timestep;
    int gentime = curtime;
    int tmp = 0;
    while(frames--){
        int agentCount =  generatePerFrame();
        tmp += agentCount;
        curtime++;
    }
    if(car_num + tmp > total_num) //最后一帧已经超过了
        tmp = total_num - car_num;
    
    car_num += tmp;
    readygo_num += tmp;

    //LOG_DEBUG(my2string("generate num is ", tmp , ", time is ", gentime));
}

int DBFETE::generatePerFrame(){
    
    //需要总人数、最小值、最大值
    int agentCount = 0;
    double timestep = 0.1;
    double genAgentTime = timestep * curtime;

    if(genAgentTime < min_num){
       genCount = 0; 
    }
    else if(genAgentTime >= min_num && genAgentTime <= mean_num){
        genCount += genAgentNumMax * (genAgentTime - min_num) * timestep / (mean_num - min_num);
    }
    else if(genAgentTime > mean_num && genAgentTime <= max_num){
        genCount += genAgentNumMax * (max_num - genAgentTime) * timestep / (max_num - mean_num);
    } 
    else
    {
        genCount += genAgentNumMax;
    }
    while(genCount >= 1){
        agentCount ++;
        genCount --;
    }

    return agentCount;

}

void DBFETE::doUpdate(){ 

    generate();
    //通过generate生成系统的入量(特殊的Node模型)
    
    //根据node model产生增量(根据t-1)
    for(auto &mnode : nodes){
        int node_id = mnode.first;
        vector<float> input = gen_node_feature(node_id);
        node_models[node_id]->predict(input,nodes[node_id]->inflow);
    }

    //根据link model产生pool->buffer的(根据t-1)
    for(auto &mlink:links){
        const int& link_id = mlink.first;
        vector<float> input = gen_link_feature(link_id);
        link_models[link_id]->predict(input,links[link_id]->pool2buffer);
    }

    //上述的数据均为tmp数据，在使用模型的时候不能更新任何一个数据
    //inflow同时受 poolnum 和 buffer的大小的限制
	for(auto &mnode : nodes){
        int node_id = mnode.first;
        if(startIds.find(node_id) != startIds.end()) nodes[node_id]->inflow = min(readygo_num, (double)nodes[node_id]->inflow); //发车限制
        //处理条件约束
        nodes[node_id]->inflow = min(nodes[node_id]->capacity, nodes[node_id]->inflow); //容量限制
		for(auto linkid : mnode.second->flinks){
            nodes[node_id]->inflow = min(links[linkid]->buffernum, (double)nodes[node_id]->inflow); //存量限制
		}
		for(auto linkid: mnode.second->tlinks){
            nodes[node_id]->inflow = min(links[linkid]->maxpoolnum - links[linkid]->poolnum, (double)nodes[node_id]->inflow);// 空间限制
		}


        //更新
        
        if(startIds.find(node_id) != startIds.end()) readygo_num -= nodes[node_id]->inflow; //更新origin
		for(auto linkid : mnode.second->flinks){
            links[linkid]->buffernum -= nodes[node_id]->inflow; //更新前向link的buffernum
		}
		for(auto linkid: mnode.second->tlinks){
            links[linkid]->poolnum += nodes[node_id]->inflow; //更新后向link的poolnum
        }
	}



    //计算系统输入输出
    int endId = *endIds.begin();
    dest_num += nodes[*endIds.begin()]->inflow;
    origin_num -= nodes[*startIds.begin()]->inflow;
    
    //计算完毕之后，统一更新pool和buffer数据
    for(auto &mlink : links){
        int link_id = mlink.first;

        links[link_id]->pool2buffer = min(
                min(links[link_id]->poolnum, (double)links[link_id]->pool2buffer),
                links[link_id]->maxbuffernum - links[link_id]->buffernum);

        links[link_id]->poolnum -= links[link_id]->pool2buffer;
        links[link_id]->buffernum += links[link_id]->pool2buffer;
    }
}


void DBFETE::start(){
    while(!Finished){
        showStatus();
        doUpdate();
        isClean(); //每次判断是否为空了
        boost::thread::sleep(boost::get_system_time()+boost::posix_time::milliseconds(_config.pausetime));
    }
}

void DBFETE::check(){
   //合理性检测 
}

bool DBFETE::isClean(){
    for(auto &mlink : links){
        if(mlink.second->poolnum !=0 ||mlink.second->buffernum !=0)
        {
            Finished = false;
            return false;
        }
    }

    //都为0 ,但是目标需求暂未达到
    if(car_num < total_num){
        Finished = false;
        return false;
    }

    Finished = true;
    return true;
}


vector<float> DBFETE::gen_node_feature(int node_id){
    float period = curtime % 600 / 60;
    switch(node_id){
        case 1949:  return {(float)links[1949]->poolnum, (float)period};
        case 1951:  return {(float)links[1949]->buffernum, (float)links[1951]->poolnum ,(float) period};
        case 2077:  return {(float)links[1951]->buffernum, (float)links[2077]->poolnum ,(float) period};
        case 102076:return {(float)links[2077]->buffernum, (float)period};
    }
    
}


vector<float> DBFETE::gen_link_feature(int link_id){
    float period = curtime % 600 / 60; //TODO hard code
    switch(link_id){
        case 1949: return {(float)links[1949]->buffernum, (float)links[1949]->poolnum, (float)period};
        case 1951: return {(float)links[1951]->buffernum, (float)links[1951]->poolnum, (float)period};
        case 2077: return {(float)links[2077]->buffernum, (float)links[2077]->poolnum, (float)period};
        //case 102076: return {period, links[2077]->buffernum};
    }
}

void DBFETE::showStatus(){

    //for single path, just one end point.
    std::stringstream os;
    os << "[frame "  << setw(6) << curtime << "] ";

    //输出源点demand
    os << "(" << BOLDRED << setw(4) << origin_num << "|" << setw(4) << readygo_num << RESET << ")" << BOLDRED << "⇶ " << RESET ;

    auto it_node = nodes.begin();
    auto it_link = links.begin();

    //交替输出
    for(auto &path : paths){
        for(auto id : path){
            if(nodes.find(id) != nodes.end())
                os << *(nodes[id]);
            if(links.find(id) != links.end())
                os << *(links[id]);
        }
    }

    //输出超级终点汇入量
    os << BOLDGREEN << "⇶ " << RESET << "("<< BOLDGREEN << setw(4) << dest_num << RESET << ")";
    LOG_INFO(os.str());
}

