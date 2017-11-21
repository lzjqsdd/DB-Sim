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
	this->sample_linkids = config.sample_linkids;
	this->sample_nodeids = config.sample_nodeids;
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
		this->sample_linkids = config.sample_linkids;
		this->sample_nodeids = config.sample_nodeids;
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

	if(config.sample){
		os << std::endl << "sample : " << endl << "{" << endl;
		os << "\tsample_linkids: ";
		for(auto linkid : config.sample_linkids){
			os << " " << linkid;
		}
		os << endl << "\tsample_nodeids: ";
		for(auto nodeid : config.sample_nodeids){
			os << " " << nodeid;
		}
		os << endl << "}";
	}
    return os;
}

