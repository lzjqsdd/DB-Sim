#include "fete.h"

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
    _manager->loadLinks(_config.pathdir, links);
    _manager->loadNodes(_config.nodedir, nodes);
}

void FETE::init(){
    //加载路网
    loadNetwork();
}

Config FETE::getConfig(){
    return _config;
} 

void FETE::doUpdate(){ 
    //计算每个增量
    //更新队列
}
void FETE::start(){
    while(!Finished){
        if(Finished) return;
        TotalTime += _config.timestep;
        doUpdate();
        isClean(); //每次判断是否为空了
    }
}
void FETE::check(){

}

bool FETE::isClean(){

    for(auto plink : _links){
        if(plink->wait_queue.size() != 0){
            return false;
        }
    }
    Finished = true;
    return true;
}

