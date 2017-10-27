#include "config.h"

Config::Config(){
    config_path = "./config.conf";
}

Config::Config(const Config& config){
    timestep = config.timestep;
    config_path = config.config_path;
}

Config& Config::Operator=(const Config& config){
    if(this!=&config){
        timestep = config.timestep;
        config_path = config.config_path;
    }
    return *this;
}

