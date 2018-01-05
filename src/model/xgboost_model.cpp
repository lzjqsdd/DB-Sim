#include "xgboost_model.h"
#include "../core/type.h"

#include <assert.h>
#include <boost/filesystem.hpp>
namespace bf = boost::filesystem;

XGBoostModel::XGBoostModel(){
   LOG_TRACE("Ctor XGBoostModel"); 
}


//加载模型文件
void XGBoostModel::init(const Config& config) {

   LOG_DEBUG(my2string("\n\tusing xgboost model. \n\tversion:", config.xgboost_version, "\n\t", config.xgboost_desc));

   //init booster_list
   size_t node_num = config.xgboost_model.size();
   for(auto model_config: config.xgboost_model){
       booster_list[model_config.node_id] = NULL;
   }

   //从指定路径加载
   for(int i = 0; i< node_num; ++i){
       int node_id =  config.xgboost_model[i].node_id;
       string model_file =  config.xgboost_model[i].model_file;

       if( bf::exists(model_file) ){ 

           XGBoosterCreate(NULL, 0, &booster_list[node_id]);
           XGBoosterLoadModel(booster_list[node_id] , model_file.c_str());
           LOG_DEBUG(my2string("load node ", node_id , "done."));

       }
       else{
           free();
           LOG_FATAL(my2string(model_file,"not found!"));
           exit(-1);
       }
   }
}

void XGBoostModel::train() {

   LOG_TRACE("Train XGBoostModel"); 

}

void XGBoostModel::predict(const vector<float> &input, vector<float> &output) {
   LOG_TRACE("predict XGBoostModel"); 
}


void XGBoostModel::predict(int node_id, const vector<float> &input, float &output) {
   LOG_TRACE("predict XGBoostModel"); 

   vector<vector<float>> test_data = {input};
   DMatrixHandle h_test = NULL;

   XGDMatrixCreateFromMat((float *) &input[0], 1, input.size(), 0, &h_test);

   const float *result;
   bst_ulong out_len;
   XGBoosterPredict(booster_list[node_id], h_test, 0, 0, &out_len, &result);
   assert(out_len == 1);
   output  = result[0];

   XGDMatrixFree(h_test);

}

void XGBoostModel::predict(const map<int,vector<float>>&input, map<int, vector<float>> &output) {
    //TODO
}


void XGBoostModel::free(){
    for(auto node_booster : booster_list){
        if(node_booster.second) //NOT NULL
            XGBoosterFree(node_booster.second);
    }
}

XGBoostModel::~XGBoostModel() { 
    LOG_TRACE("dstor XGBoostModel"); 
}
