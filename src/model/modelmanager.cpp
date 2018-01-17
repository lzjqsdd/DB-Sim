#include "modelmanager.h"

shared_ptr<ModelManager> ModelManager::_modelManager = shared_ptr<ModelManager>(new ModelManager());

ModelManager::ModelManager(){
    char name[20];
    strcpy(name, "FeteModel");
    Py_SetProgramName(name);
    Py_Initialize();
}

shared_ptr<ModelManager> ModelManager::getModelManager(){
    return _modelManager;
}

ModelManager::~ModelManager(){
   Py_Finalize(); 
}

void ModelManager::init(const Config& config){
   Config tmpconfig(config);
   _config = std::move(tmpconfig); 
}

void ModelManager::Test()
{
    PyRun_SimpleString("print 'hello fete' \n");
}

shared_ptr<Model> ModelManager::getRandomForestModel(){
    shared_ptr<Model> rfmodel = shared_ptr<Model>(new RandomForestModel()); 
    return rfmodel;
}

shared_ptr<Model> ModelManager::getXGBoostModel(){
    shared_ptr<Model> xgboost_model = shared_ptr<Model>(new XGBoostModel()); 
    return xgboost_model;
}

shared_ptr<Model> ModelManager::getXGBoostModelByNode(const int& node_id){ 
    
    shared_ptr<Model> xgboost_model = shared_ptr<Model>(new XGBoostModel()); 
    size_t node_num = _config.xgboost_node_model.size();
    cout << "node_num :" << node_num << endl;
    bool found = false;
    for(int i=0; i< node_num; ++i){
        if(node_id == _config.xgboost_node_model[i].mid){
            xgboost_model->init(_config.xgboost_node_model[i].model_file);
            found = true;
            break;
        }
    }
    if(!found){ 
        LOG_FATAL(my2string("modelmanager can't init node ",node_id, " model!!!"));
        exit(-1);
    }
    LOG_DEBUG(my2string("\n\tUsing xgboost model for node ",node_id ,".\n\tversion:", _config.xgboost_version, "\n\t", _config.xgboost_desc));

    return xgboost_model;
}

shared_ptr<Model> ModelManager::getXGBoostModelByLink(const int& link_id){ 
    
    shared_ptr<Model> xgboost_model = shared_ptr<Model>(new XGBoostModel()); 
    size_t link_num = _config.xgboost_link_model.size();
    cout << "link_num :" << link_num << endl;
    bool found = false;
    for(int i=0; i< link_num; ++i){
        if(link_id == _config.xgboost_link_model[i].mid){
            xgboost_model->init(_config.xgboost_link_model[i].model_file);
            found = true;
            break;
        }
    }
    if(!found){ 
        LOG_FATAL(my2string("modelmanager can't init link ",link_id, " model!!!"));
        exit(-1);
    }
    LOG_DEBUG(my2string("\n\tUsing xgboost model for link " , link_id , ".\n\tversion: ", _config.xgboost_version, "\n\t", _config.xgboost_desc));

    return xgboost_model;
}

shared_ptr<Model> ModelManager::getSVMModel(){
    shared_ptr<Model> svm_model = shared_ptr<Model>(new SVMModel()); 
    return svm_model ;
}

