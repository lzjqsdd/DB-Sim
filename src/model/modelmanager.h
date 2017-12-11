// 加载model
#ifndef __MODEL_MANAGER_H__
#define __MODEL_MANAGER_H__

#include <memory>
#include <Python.h>

using namespace std;
//model manager
//init python environment,load model
class ModelManager{
public:
    static shared_ptr<ModelManager> getModelManager();
    void Test();
    ~ModelManager();

protected:
    ModelManager();
private:
    static shared_ptr<ModelManager> _modelManager;
};

#endif
