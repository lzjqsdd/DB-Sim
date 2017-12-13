#include <iostream>
#include <cstdio>
#include <sstream>
#include <chrono>

#include <boost/program_options.hpp>


#include "./core/type.h"
#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"
#include "./core/preprocess.h"
#include "./core/manager.h"

#include "./core/bfete.h"
#include "./core/cfete.h"
#include "./core/gfete.h"
#include "./core/tfete.h"

#include "./model/modelmanager.h"
#include "./model/model.h"

#include "./utils/tinyxml2.h"


using namespace std;
using namespace tinyxml2;

void TestModel()
{
    shared_ptr<ModelManager> modelManager = ModelManager::getModelManager();
    modelManager->Test();
    shared_ptr<Model> rfmodel = modelManager->getRandomForestModel();
    rfmodel->init();

    rfmodel = modelManager->getXGBoostModel();
    rfmodel->init();
}


void sample()
{
    //加载配置文件
    Config config("../config/config.conf");
    shared_ptr<Manager> manager = Manager::getManager();
    manager->init(config);

    //初始化日志等级
    initlog(config.log_level);

    //创建推演对象
    TFETE tfete(config); //主要处理类
	FETEIf &f = tfete;
	f.init();
    LOG_TRACE("sample ...");
    PProcess processor(config.data_path,"car",config.timestep,config.sample_outpath,f.paths, f.nodes, f.links);
    processor.init();
    processor.clean();

    //sample by nodes
    vector<int> nodes;
    for(auto node:f.nodes) nodes.push_back(node.first);
    if(config.sample_nodeids.size() != 0)
        processor.doSampleByNode(config.sample_nodeids);
    else
        processor.doSampleByNode(nodes);

}


void simulation()
{
    //加载配置文件
    Config config("../config/config.conf");

    shared_ptr<Manager> manager = Manager::getManager();
    manager->init(config);

    //初始化日志等级
    initlog(config.log_level);

    //创建推演对象
    TFETE tfete(config); //主要处理类
	FETEIf &f = tfete;
	f.init();

    auto stime = chrono::system_clock::now();
    f.start();
    auto etime = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(etime-stime);

    LOG_TRACE(my2string("Total Time is : ", duration.count()," ms"));
}


int main(int argc, char *argv[])
{

    namespace po = boost::program_options;
    po::options_description desc("Usage");
    desc.add_options()
        ("help,h","show help")
        ("sample,s","sample for node and link")
        ("simulation,S", "simulation for fete")
        ("test,t","Test each model")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc),vm);
    po::notify(vm);

    if(vm.count("help")){
        cout << desc << "\n";
        return 1;
    }
    else if(vm.count("sample")){
        sample();
    }
    else if(vm.count("simulation")){
        simulation();
    }
    else if(vm.count("test")){
        TestModel();
    }
    else
    {
        cout << desc << "\n";
        return 1;
    }
    return 0;
    
}
