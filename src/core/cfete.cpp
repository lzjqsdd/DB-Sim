#include "cfete.h"
#include "type.h"
#include "../utils/tool.hpp"

#include <set>
#include <algorithm>

CFETE::CFETE(){
    Finished = false;
}

CFETE::CFETE(const Config &config){ 
    this->_config = config;
    this->Finished = false;
}

CFETE& CFETE::operator=(const CFETE& fete){
    //暂未处理
}


/**********************************/


void CFETE::loadNetwork(){
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

void CFETE::init(){
    //加载路网
    LOG_TRACE("init fete ...");
    loadNetwork();
    curtime = 0;
    curnum = 0;
}

Config CFETE::getConfig(){
    return _config;
}

vector<vector<int>> CFETE::getPaths(){
    return paths;
}

void CFETE::generate(){
	LOG_DEBUG("Todo ...");
}

//以下实现的是grawon's的模型
void CFETE::doUpdate(){ 
    //计算每个增量
    generate();
}


void CFETE::start(){
    while(!Finished){
        LOG_DEBUG(my2string("==============Current Time is : " , curtime, "========================="));
        if(Finished) return;
        curtime += _config.timestep;
        doUpdate();
        isClean(); //每次判断是否为空了
    }
	LOG_FATAL(my2string("Total time is : " , curtime));
}

void CFETE::check(){
    
}

bool CFETE::isClean(){
	LOG_DEBUG("Todo ...");
	Finished = true;
    return true;
}
