// RandomForest model
#ifndef __RF_MODEL_H__
#define __RF_MODEL_H__

#include "model.h"

class RandomForestModel: public Model{
    public:
        RandomForestModel();
        void init(const string& model_file); //init model args
        void train(); //train model,may never use
        void predict(const vector<float> &input, vector<float> &output);
        ~RandomForestModel();
};

#endif
