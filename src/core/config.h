#ifndef __CONFIG_H__
#define __CONFIG_H__

#include<iostream>
using namespace std;


class Config{
    public:
        Config();
        Config(const Config& config);
        Config& operator=(const Config& config);

        int timestep; //example 30seconds per iteration
        string config_path;
        string pathdir;
        string nodedir;
};

#endif
