#include "tfete.h"
#include "type.h"
#include "../utils/tool.hpp"

#include <set>
#include <algorithm>

TFETE::TFETE(){
    Finished = false;
}

TFETE::TFETE(const Config &config){ 
    this->_config = config;
    this->Finished = false;
}

TFETE& TFETE::operator=(const TFETE& fete){
    //暂未处理
}


/**********************************/


void TFETE::loadNetwork(){
    //加载links和nodes
    _manager->loadLinks(_config.pathdir, links, paths);
    _manager->loadNodes(_config.nodedir, nodes);

	//建立link的前后关系
	_manager->fillLinks(paths,links);

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

void TFETE::init(){
    //加载路网
    LOG_TRACE("init Tfete ...");
    loadNetwork();
    curtime = 0;
    curnum = 0;
}

Config TFETE::getConfig(){
    return _config;
}

vector<vector<int>> TFETE::getPaths(){
    return paths;
}


void TFETE::generate(){
    //根据起点的link进入场景
    for(auto sid : startIds){
        auto link = links[sid];
    }
}

//以下实现的是grawon's的模型
void TFETE::doUpdate(){ 
    //计算每个增量
    generate();
}
void TFETE::start(){
    while(!Finished){
        LOG_DEBUG(my2string("==============Current Time is : " , curtime, "========================="));
        if(Finished) return;
        curtime += _config.timestep;
        doUpdate();
        isClean(); //每次判断是否为空了
    }
	LOG_FATAL(my2string("Total time is : " , curtime));
}

void TFETE::check(){
    
}

bool TFETE::isClean(){
    for(auto mlink : links){
        if(mlink.second->wait_queue.size() != 0){
            return false; 
        }
    }
    Finished = true;
    return true;
}
