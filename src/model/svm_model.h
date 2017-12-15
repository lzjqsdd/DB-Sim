#ifndef __SVM_MODEL_H__
#define __SVM_MODEL_H__
// SVR Model
#include "model.h"
class SVMModel: public Model{
    public:
        SVMModel();
        void init();
        void train();
        void predict(const vector<int>&input, vector<int>& output);
        ~SVMModel();
};

#endif
