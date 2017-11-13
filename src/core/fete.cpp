#include "fete.h"
#include "type.h"
#include "../utils/tool.hpp"

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
    LOG_TRACE("init fete ...");
    loadNetwork();
    curtime = 0;
    curnum = 0;
}

Config FETE::getConfig(){
    return _config;
} 

void FETE::doUpdate(){ 
    //计算每个增量
    for(auto mlink : links){
		LOG_DEBUG(my2string("linkid is : " ,mlink.second->id));
        //判断当前link是否是起点
        if(startIds.find(mlink.first) != startIds.end()){
            LOG_DEBUG(my2string("startpoint: " , mlink.first));
            //如果是起点,判断是否有空闲空间
            auto link = mlink.second;
            while(link->totalnum > link->poolnum){
                Agent * agent = new Agent(++curnum, link->id);
                //当前进入的车辆的到达时间，等于 （当前时间点 + 队列最后的车辆到达的时间 + 自由时间)
                agent->arrival_time = curtime + link->length * 1.0 / CARLEN; //先简单处理，按照全自由的时间
                link->poolnum --;
				link->totalnum ++;
				//LOG_DEBUG(my2string("linkid is: ", link->id , "\t curnum is : ", curnum));
            }
        }
        else{
            //如果不是起点，根据目标link限制条件来处理。
        }
    }
    //更新队列
}
void FETE::start(){
    while(!Finished){
        if(Finished) return;
        curtime += _config.timestep;
        LOG_DEBUG(my2string(curtime));
        doUpdate();
        isClean(); //每次判断是否为空了
		Finished = true;
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

