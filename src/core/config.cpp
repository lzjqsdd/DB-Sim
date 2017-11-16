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
    for(auto demand : config.demands){
        this->demands[demand.first] = demand.second;
    }
}

Config& Config::operator=(const Config& config){
    if(this!=&config){
        this->timestep = config.timestep;
        this->config_path = config.config_path;
        this->pathdir = config.pathdir;
        this->nodedir = config.nodedir;
        this->log_level = config.log_level;
        for(auto demand : config.demands){
            this->demands[demand.first] = demand.second;
        }
    }
    return *this;
}

//非成员函数
ostream& operator<<(ostream& os, const Config& config){
    os << endl << "Current Config is :" << endl
        << "{ " << endl
        << "    Timestep is " << config.timestep << endl
        << "}";
    os << std::endl << "demand : "<< endl << "{" << endl;
    for(auto demand: config.demands){
        os << demand.first << ":" << demand.second << endl;
    }
    os << "}";
    return os;
}

