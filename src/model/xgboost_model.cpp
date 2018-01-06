#include "xgboost_model.h"
#include "../core/type.h"

#include <assert.h>
#include <boost/filesystem.hpp>
namespace bf = boost::filesystem;

XGBoostModel::XGBoostModel(){
   LOG_TRACE("Ctor XGBoostModel"); 
}


//加载模型文件
void XGBoostModel::init(const string& model_file) {

    booster = NULL;

    if( bf::exists(model_file) ){ 
        XGBoosterCreate(NULL, 0, &booster);
        XGBoosterLoadModel(booster , model_file.c_str());
    }
    else{
        free();
        LOG_FATAL(my2string(model_file," not found!"));
        exit(-1);
    }
}

void XGBoostModel::train() {

   LOG_TRACE("Train XGBoostModel"); 

}

void XGBoostModel::predict(const vector<float> &input, vector<float> &output) {
   LOG_TRACE("predict XGBoostModel"); 
}


void XGBoostModel::predict(const vector<float> &input, float &output) {
   LOG_TRACE("predict XGBoostModel"); 

   vector<vector<float>> test_data = {input};
   DMatrixHandle h_test = NULL;

   XGDMatrixCreateFromMat((float *) &input[0], 1, input.size(), 0, &h_test);

   const float *result;
   bst_ulong out_len;
   XGBoosterPredict(booster, h_test, 0, 0, &out_len, &result);
   assert(out_len == 1);
   output  = result[0];

   XGDMatrixFree(h_test);

}

void XGBoostModel::predict(const map<int,vector<float>>&input, map<int, vector<float>> &output) {
    //TODO
}


void XGBoostModel::free(){
    if(booster) XGBoosterFree(booster);
}

XGBoostModel::~XGBoostModel() { 
    LOG_TRACE("dstor XGBoostModel"); 
}
