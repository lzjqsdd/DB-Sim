// 加载model
#ifndef __MODEL_MANAGER_H__
#define __MODEL_MANAGER_H__

#include <memory>
#include <Python.h>

#include "../core/config.h"
#include "rf_model.h"
#include "xgboost_model.h"
#include "svm_model.h"

using namespace std;
//model manager
//init python environment,load model
class ModelManager{
public:
    static shared_ptr<ModelManager> getModelManager();
    void Test();
    void init(const Config& config);
    //rf model
    shared_ptr<Model> getRandomForestModel();

    //xgboost model
    shared_ptr<Model> getXGBoostModel();
    shared_ptr<Model> getXGBoostModelByNode(const int& node_id);

    //svm model
    shared_ptr<Model> getSVMModel();


    ~ModelManager();

protected:
    ModelManager();
private:
    static shared_ptr<ModelManager> _modelManager;
    Config _config;
};

#endif
