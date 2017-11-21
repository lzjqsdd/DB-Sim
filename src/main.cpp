#include <iostream>
#include <cstdio>
#include<sstream>


#include "./core/type.h"
#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"
#include "./core/preprocess.h"

#include "./core/bfete.h"
#include "./core/cfete.h"
#include "./core/gfete.h"
#include "./core/tfete.h"

#include "./utils/tinyxml2.h"
#include "./core/manager.h"

using namespace std;
using namespace tinyxml2;

int main()
{
    //加载配置文件
    Config config;
    Manager * manager = Manager::getManager();
    manager->loadConfig("../config/config.conf",config);
    LOG_TRACE(config);

    //初始化日志等级
    initlog(config.log_level);

    //创建推演对象
    TFETE tfete(config); //主要处理类
	FETEIf &f = tfete;

	f.init();

	//采样
	if(config.sample){
		LOG_TRACE("sample ...");
		PProcess processor(config.data_path,"car",config.timestep,config.sample_outpath,f.paths, f.nodes);
		processor.init();
		vector<int> links;
		for(auto link:f.links) links.push_back(link.first);
		if(config.sample_linkids.size() != 0)
			processor.doSampleByLink(config.sample_linkids);
		else
			processor.doSampleByLink(links);
	}
	else 
		f.start();
}
