#include "config.h"

Config::Config():
	config_path("../config"),
	log_level(logging::trivial::trace),
	sample(false),
	data_path("../data")
{
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
	this->sample = config.sample;
	this->data_path = config.data_path;
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
		this->sample = config.sample;
		this->data_path = config.data_path;
    }
    return *this;
}

//非成员函数
ostream& operator<<(ostream& os, const Config& config){
    os << endl << "Current Config is :" << endl
        << "{ " << endl
		<< "\tSample is " << config.sample << endl
        << "\tTimestep is " << config.timestep << endl
        << "\tDataPath is " << config.data_path<< endl
        << "}";
    os << std::endl << "demand : "<< endl << "{" << endl;
    for(auto demand: config.demands){
        os << "\t" << demand.first << ":" << demand.second << endl;
    }
    os << "}";
    return os;
}

