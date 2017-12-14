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


void sample(const Config& config)
{
    //加载配置文件
    shared_ptr<Manager> manager = Manager::getManager();
    manager->init(config);

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


void simulation(const Config& config, model_type type)
{
    shared_ptr<Manager> manager = Manager::getManager();
    manager->init(config);

    //创建推演对象
	shared_ptr<FETEIf> model = shared_ptr<FETEIf>();
    
    switch(type){
        case FETE:      model = manager->getFETEModel();    break;
        case CEIL:      model = manager->getCeilModel();    break;
        case GAWRON:    model = manager->getGawronModel();  break;
        case TEST:      model = manager->getTestModel();    break;
    }

	model->init();
    auto stime = chrono::system_clock::now();
    model->start();
    auto etime = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(etime-stime);

    LOG_FATAL(my2string("Total Time is : ", duration.count()," ms"));
}


int main(int argc, char *argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("\nfete [options] [ceil|test|gawron|fete] ");
    desc.add_options()
        ("help,h","show help")
        ("sample,s","sample for node and link")
        ("simulation,S", po::value< vector<string> >(),"simulation for fete")
        ("test,t","Test each model")
        ;

    po::positional_options_description p;
    p.add("simulation",-1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc,argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        cout << desc << "\n";
        return 1;
    }
    else if(vm.count("sample")){
        Config config("../config/config.conf");
        initlog(config.log_level);
        LOG_TRACE(config);
        sample(config);
    }
    else if(vm.count("simulation")){
        Config config("../config/config.conf");
        initlog(config.log_level);
        LOG_TRACE(config);
        vector<string> simu_args = vm["simulation"].as< vector<string> >();
        for(auto sarg : simu_args) simulation(config, str2type(sarg));
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
