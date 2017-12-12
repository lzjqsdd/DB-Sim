// XGBoost model
#ifndef __XGBOOST_MODEL_H__
#define __XGBOOST_MODEL_H__

#include "model.h"

class XGBoostModel: public Model{
    public:
        XGBoostModel();
        void init(); //init model args
        void train(); //train model,may never use
        void predict(const vector<int> &input, vector<int> &output);
        ~XGBoostModel();
};

#endif
