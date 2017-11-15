#include "fete.h"
#include "type.h"
#include "../utils/tool.hpp"

#include <set>
#include <algorithm>

FETE::FETE(){
    Finished = false;
}

FETE::FETE(const Config &config){ 
    this->_config = config;
    this->Finished = false;
}

FETE& FETE::operator=(const FETE& fete){
    //暂未处理
}


/**********************************/


void FETE::loadNetwork(){
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

	//totalnum
	total_num = 5;
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

//以下实现的是grawon's的模型
void FETE::doUpdate(){ 
    //计算每个增量
    for(auto mlink : links){
        //判断当前link是否是起点
		auto link = mlink.second;
        if(startIds.find(mlink.first) != startIds.end()){
            LOG_TRACE(my2string("startpoint: " , mlink.first));
            //如果是起点,判断是否有空闲空间
            while(total_num > curnum && link->totalnum > link->poolnum){
                Agent * agent = new Agent(++curnum, link->id);
                //当前进入的车辆的到达时间，等于 （当前时间点 + 队列最后的车辆到达的时间 + 自由时间)
                agent->arrival_time = curtime + link->length * 1.0 / CARLEN; //先简单处理，按照全自由的时间
				LOG_DEBUG(my2string("Agent",agent->id," comes in link", link->id));
				link->wait_queue.push(agent); //加入到当前队列中
                link->poolnum ++;
				//LOG_DEBUG(my2string("linkid is: ", link->id , "\t curnum is : ", curnum));
            }
        }
		else if(endIds.find(mlink.first) != endIds.end()){
			//如果是终点,按照量给出
			int delta = 10; //每个delta可以出的车数
			int min_num = std::min(delta,int(link->poolnum));
			while(min_num--)
			{
				LOG_DEBUG("running ...")
				if(link->wait_queue.empty()) break; //和poolnum对应
				auto agent = link->wait_queue.top();
				LOG_DEBUG(my2string("Agent", agent->id, " leaves scene..."));
				link->wait_queue.pop(); //直接出场景了
				link->poolnum --;
			}
		}
        else{
            //如果不是起点，根据目标link限制条件来处理。
			//查找link的前后关系
			for(auto nid : link->nids){
				auto nlink = links[nid];
				//当前队列头到达末尾的时间超过了当前时间轴，
				//并且目标队列由空间，则进入目标队列
				//当前为贪心策略，使劲服务其中一个
				if(link->wait_queue.empty()) break;
				auto agent = link->wait_queue.top();
				while(agent->arrival_time > curtime
					&&  nlink->totalnum > nlink->poolnum){

					LOG_DEBUG("end ...")
					link->wait_queue.pop();
					link->poolnum--;

					//计算进入下一个队列末尾的时间
					agent->arrival_time = curtime + nlink->length * 1.0 / CARLEN; //先简单处理，按照全自由的时间
					nlink->wait_queue.push(agent);
					nlink->poolnum ++;
				}
			}
        }
    }
    //更新队列
}
void FETE::start(){
    while(!Finished){
        if(Finished) return;
        curtime += _config.timestep;
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

