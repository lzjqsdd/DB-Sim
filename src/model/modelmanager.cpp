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
