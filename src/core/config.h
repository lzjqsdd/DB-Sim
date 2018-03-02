#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "type.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <libconfig.h++>

#include "../core/type.h"
#include "../core/link.h"
#include "../core/node.h"

using namespace std;

struct ModelConfig
{ 
    int mid;
    string model_file;
    //TODO model version management
};


class Config{
    public:
        Config();
        Config(const string& config_path);
        Config(const Config& config);
        Config& operator=(const Config& config);
        friend ostream& operator<<(ostream& os, const Config& config);
        void init(const string& config_path); //load config

        string config_path;

        //global config
		bool sample; //是否采样
        int timestep; //example 30seconds per iteration
        int period_dur; //每个周期持续的长度
        string pathdir;
        string nodedir;
        logging::trivial::severity_level log_level;
        int pausetime;

        //demands config
        map<int,int> demands;

        //generate
        int gen_min_frame;
        int gen_max_frame;

        //sample config
		string data_path; //原始数据所在位置
		vector<int> sample_linkids; //需要采样的link
		vector<int> sample_nodeids; //需要采样的node
        string data_prefix; //原始数据的命名前缀
		string sample_outpath; //采样输出位置
        double poolsize; //pool length after node
        double buffersize; //buffer length before node
        bool cleanall; //clean all sample file


        //simulation config
        bool sim_write;
        string sim_prefix;
        string sim_path;

        //train and model config
        vector<ModelConfig> xgboost_node_model; //xgboost的模型文件目录
        vector<ModelConfig> xgboost_link_model; //xgboost的模型文件目录
        string xgboost_version; //xgboost当前使用的模型
        string xgboost_desc; //当前xgboost的一些描述信息


};

#endif
