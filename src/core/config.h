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
        string pathdir;
        string nodedir;
        logging::trivial::severity_level log_level;

        //demands config
        map<int,int> demands;


        //sample config
		string data_path; //原始数据所在位置
		vector<int> sample_linkids; //需要采样的link
		vector<int> sample_nodeids; //需要采样的node
        string data_prefix; //原始数据的命名前缀
		string sample_outpath; //采样输出位置
        double poolsize; //pool length after node
        double buffersize; //buffer length before node
};

#endif
