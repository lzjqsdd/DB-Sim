#include "config.h"

Config::Config(){
    config_path = "./config.conf";
}

Config::Config(const Config& config){
    timestep = config.timestep;
    config_path = config.config_path;
    pathdir = config.pathdir;
    nodedir = config.nodedir;
}

Config& Config::operator=(const Config& config){
    if(this!=&config){
        timestep = config.timestep;
        config_path = config.config_path;
        pathdir = config.pathdir;
        nodedir = config.nodedir;
    }
    return *this;
}

