#include "tfete.h"
#include "type.h"
#include "../utils/tool.hpp"

#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>

TFETE::TFETE(){
    Finished = false;
}

TFETE::TFETE(const Config &config){ 
    this->_config = config;
    this->Finished = false;
}

TFETE& TFETE::operator=(const TFETE& fete){
}


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


void TFETE::loadStaticData(const string& datapath)
{
	//加载link采样的数据
	//map<frame,map<linkid,pair<inflow,outflow>>
	for(auto mlink : links){
		try{
			string link_datapath = my2string(datapath,"/",mlink.first,"_sample.txt");
			fstream fin(link_datapath.c_str(), std::ifstream::in);
			string line;
			int frame,inflow,outflow,poolnum;
			while(std::getline(fin,line)){
				istringstream is(line);
				is >> frame >> inflow >> outflow >> poolnum;
				static_data[mlink.first][frame] = new LinkData(inflow,outflow,poolnum);
			}
			LOG_TRACE(my2string("load static data link : ",mlink.first, " done."));
		}catch(...){
			LOG_FATAL(my2string("read static data link",mlink.first,"error!"));
			exit(1);
		}
	}
}



void TFETE::init(){
    //加载路网
    LOG_TRACE("init Tfete ...");
    loadNetwork();
	loadStaticData(_config.sample_outpath);
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
    //generate();
	//变化以link为更新对象
	//迭代以node进行迭代
	for(auto &mnode : nodes){
		for(auto linkid : mnode.second->flinks){
			//更新flink的出量
			if(static_data[linkid].find(curtime) != static_data[linkid].end())
				links[linkid]->poolnum -= (static_data[linkid][curtime]->outflow);
		}
		for(auto linkid: mnode.second->tlinks){
			//更新tlink的入量
			if(static_data[linkid].find(curtime) != static_data[linkid].end())
				links[linkid]->poolnum += (static_data[linkid][curtime]->inflow);
		}
	}

	//string ss="links : ";
	//for(auto &mlink: links)
	//	ss += ("," + to_string(int(mlink.first)));
	//LOG_DEBUG(ss);

	string ss=to_string(int(curtime)) + " status: ";
	for(auto &mlink: links)
		ss += ("," + to_string(int(mlink.second->poolnum)));
	LOG_DEBUG(ss);
}
void TFETE::start(){
    while(!Finished){
        //LOG_DEBUG(my2string("==============Current Time is : " , curtime, "========================="));
        if(Finished) return;
        doUpdate();
        isClean(); //每次判断是否为空了
        curtime += _config.timestep;
    }
	LOG_FATAL(my2string("Total time is : " , curtime));
}

void TFETE::check(){
    
}

bool TFETE::isClean(){
	if(curtime <= 1800+_config.timestep) return false;
    for(auto mlink : links){
        if(mlink.second->poolnum != 0){
            return false; 
        }
    }
    Finished = true;
    return true;
}
