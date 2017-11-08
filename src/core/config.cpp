#include "config.h"

Config::Config(){
    config_path = "./config.conf";
    log_level = logging::trivial::trace;
}

Config::Config(const Config& config){
    timestep = config.timestep;
    config_path = config.config_path;
    pathdir = config.pathdir;
    nodedir = config.nodedir;
    log_level = config.log_level;
}

Config& Config::operator=(const Config& config){
    if(this!=&config){
        timestep = config.timestep;
        config_path = config.config_path;
        pathdir = config.pathdir;
        nodedir = config.nodedir;
        log_level = config.log_level;
    }
    return *this;
}

//非成员函数
ostream& operator<<(ostream& os, const Config& config){
    os << "Current Config is :" << endl
        << "{ " << endl
        << "    Timestep is " << config.timestep << endl
        << "}";
    return os;
}

