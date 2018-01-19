#include "dbfete.h"
#include "type.h"
#include "../utils/tool.hpp"
#include "../model/modelmanager.h"

#include <set>
#include <algorithm>

DBFETE::DBFETE(){
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
    car_num = 0;

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
    
}

Config DBFETE::getConfig(){
    return _config;
}

vector<vector<int>> DBFETE::getPaths(){
    return paths;
}

void DBFETE::generate(){
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

    LOG_DEBUG(my2string("generate num is ", tmp , ", time is ", gentime));
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
    generate(); //TODO 默认先改为StaticData
    //通过generate生成系统的入量(特殊的Node模型)
    
    map<int,float> node_inflows;
    map<int,float> link_inflows;

    //根据node model产生增量(根据t-1)
    for(auto &mnode : nodes){
        int node_id = mnode.first;
        vector<float> input; //TODO 构造input,注意特征的顺序
        node_models[node_id]->predict(input,node_inflows[node_id]);
    }

    //根据link model产生pool->buffer的(根据t-1)
    for(auto &mlink:links){
        int link_id = mlink.first;
        vector<float> input; //TODO 构造input
        link_models[link_id]->predict(input,link_inflows[link_id]);
    }

    //上述的数据均为tmp数据，在使用模型的时候不能更新任何一个数据
	for(auto &mnode : nodes){
        int node_id = mnode.first;
		for(auto linkid : mnode.second->flinks){
			//更新flink的出量
            links[linkid]->buffernum -= node_inflows[node_id];

		}
		for(auto linkid: mnode.second->tlinks){
			//更新tlink的入量
            links[linkid]->poolnum += node_inflows[node_id];
		}
	}
    
    //计算完毕之后，统一更新pool和buffer数据
    for(auto &mlink : links){
        int link_id = mlink.first;
        links[link_id]->poolnum -= link_inflows[link_id];
        links[link_id]->buffernum += link_inflows[link_id];
    }
}


void DBFETE::start(){
    while(!Finished){
        if(Finished) return;
        doUpdate();
        isClean(); //每次判断是否为空了
    }
}

void DBFETE::check(){
    
}

bool DBFETE::isClean(){
    for(auto &mlink : links){
       if(mlink.second->poolnum !=0 ||mlink.second->buffernum !=0)
       {
           Finished = true;
           return true;
       }
    }
    return false;
}


vector<float> DBFETE::gen_node_feature(int node_id){
    float period = curtime / 600 % 10;
    switch(node_id){
        case 1949: return {period, links[1949]->poolnum, links[1949]->buffernum};
        case 1951: return {period, links[1949]->poolnum , links[1949]->buffernum, links[1951]->poolnum , links[1951]->buffernum};
        case 2077: return {period, links[1951]->poolnum , links[1951]->buffernum, links[2077]->poolnum , links[2077]->buffernum};
        case 102076: return {period, links[2077]->buffernum};
    }
    
}


vector<float> DBFETE::gen_link_feature(int link_id){
    float period = curtime / 600 % 10;
    switch(link_id){
        case 1949: return {period, links[1949]->poolnum, links[1949]->buffernum};
        case 1951: return {period, links[1949]->poolnum , links[1949]->buffernum, links[1951]->poolnum , links[1951]->buffernum};
        case 2077: return {period, links[1951]->poolnum , links[1951]->buffernum, links[2077]->poolnum , links[2077]->buffernum};
        case 102076: return {period, links[2077]->buffernum};
    }
}
