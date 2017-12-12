// RandomForest model
#ifndef __RF_MODEL_H__
#define __RF_MODEL_H__

#include "model.h"

class RandomForestModel: public Model{
    public:
        RandomForestModel();
        void init(); //init model args
        void train(); //train model,may never use
        void predict(const vector<int> &input, vector<int> &output);
        ~RandomForestModel();
};

#endif
