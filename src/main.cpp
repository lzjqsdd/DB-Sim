#include <iostream>
#include <cstdio>
#include<sstream>
#include<chrono>


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
    shared_ptr<Manager> manager = Manager::getManager();
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
		processor.clean();

		//sample by link
		vector<int> links;
		for(auto link:f.links) links.push_back(link.first);

		if(config.sample_linkids.size() != 0)
			processor.doSampleByLink(config.sample_linkids);
		else
			processor.doSampleByLink(links);

		//sample by nodes
		vector<int> nodes;
		for(auto node:f.nodes) nodes.push_back(node.first);
		if(config.sample_nodeids.size() != 0)
			processor.doSampleByNode(config.sample_nodeids);
		else
			processor.doSampleByNode(nodes);

	}
	else{
        auto stime = chrono::system_clock::now();
		f.start();
        auto etime = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(etime-stime);

        LOG_TRACE(my2string("Total Time is : ", duration.count()," ms"));
    }

}
