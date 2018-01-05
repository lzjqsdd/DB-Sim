#ifndef __SVM_MODEL_H__
#define __SVM_MODEL_H__
// SVR Model
#include "model.h"
class SVMModel: public Model{
    public:
        SVMModel();
        void init(const Config& config);
        void train();
        void predict(const vector<float>&input, vector<float>& output);
        ~SVMModel();
};

#endif
