#include "config.h"

Config::Config(){
    this->config_path = "./config.conf";
    this->log_level = logging::trivial::trace;
}

Config::Config(const Config& config){
    this->timestep = config.timestep;
    this->config_path = config.config_path;
    this->pathdir = config.pathdir;
    this->nodedir = config.nodedir;
    this->log_level = config.log_level;
}

Config& Config::operator=(const Config& config){
    if(this!=&config){
        this->timestep = config.timestep;
        this->config_path = config.config_path;
        this->pathdir = config.pathdir;
        this->nodedir = config.nodedir;
        this->log_level = config.log_level;
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

