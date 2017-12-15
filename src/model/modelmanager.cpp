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
    return xgboost_model ;
}

shared_ptr<Model> ModelManager::getSVMModel(){
    shared_ptr<Model> svm_model = shared_ptr<Model>(new SVMModel()); 
    return svm_model ;
}

