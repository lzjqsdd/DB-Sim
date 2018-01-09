#include "dbfete.h"
#include "type.h"
#include "../utils/tool.hpp"

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
    curtime = 0;
    curnum = 0;
    car_num = 0;

    total_num = 500;
    min_num = 60;
    max_num = 1800;
    mean_num = max_num/3.0 + 2.0 * min_num / 3.0; //640
    genAgentNumMax = 2.0 * total_num / (max_num - min_num); //14.367816

    genCount = 0; //表示已经生成的累计的车数,小数部分可以累计到下一次生成中，而不能直接舍弃

    
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
    generate();
}


void DBFETE::start(){
    while(!Finished){
        //LOG_DEBUG(my2string("==============Current Time is : " , curtime, "========================="));
        if(Finished) return;
        doUpdate();
        isClean(); //每次判断是否为空了
    }
}

void DBFETE::check(){
    
}

bool DBFETE::isClean(){
    if(car_num >= total_num) Finished = true;
    return true;
}
