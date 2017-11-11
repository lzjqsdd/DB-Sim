#include "fete.h"
#include "type.h"

#include <set>

FETE::FETE(){
    Finished = false;
}

FETE::FETE(const Config &config){ 
    _config = config;
    Finished = false;
}

FETE& FETE::operator=(const FETE& fete){
    //暂未处理
}


/**********************************/


void FETE::loadNetwork(){
    //加载links和nodes
    _manager->loadLinks(_config.pathdir, links, paths);
    _manager->loadNodes(_config.nodedir, nodes);

    //处理起终点
    for(auto path:paths){
        startIds.insert(path.front());
        endIds.insert(path.back());
    }
}

void FETE::init(){
    //加载路网
    LOG_DEBUG("init fete ...");
    loadNetwork();
    totaltime = 0;
}

Config FETE::getConfig(){
    return _config;
} 

void FETE::doUpdate(){ 
    //计算每个增量
    for(auto mlink : links){
        //判断当前link是否是起点

    }
    //更新队列
}
void FETE::start(){
    while(!Finished){
        if(Finished) return;
        totaltime += _config.timestep;
        LOG_DEBUG(to_string(totaltime).c_str());
        doUpdate();
        isClean(); //每次判断是否为空了
    }
}

void FETE::check(){
    
}

bool FETE::isClean(){
    for(auto mlink : links){
        if(mlink.second->wait_queue.size() != 0){
            return false;
        }
    }
    Finished = true;
    return true;
}

