// XGBoost model
#ifndef __XGBOOST_MODEL_H__
#define __XGBOOST_MODEL_H__

#include "model.h"

#include <xgboost/c_api.h>

class XGBoostModel: public Model{
    public:
        XGBoostModel();
        void init(const Config& config); //init model args
        void train(); //train model,may never use
        void predict(const vector<float> &input, vector<float> &output);
        void predict(int node_id, const vector<float> &input, float &output);
        void predict(const map<int, vector<float>> &input, map<int,vector<float>> &output);
        ~XGBoostModel();

    private:
        void free();

    private:
        map<int, BoosterHandle> booster_list;
        string version;
        string desc;
        
};

#endif
