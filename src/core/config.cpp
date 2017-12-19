#include "config.h"

Config::Config():
	config_path("../config"),
	log_level(logging::trivial::trace),
	sample(false),
	data_path("../data"),
	sample_outpath("../data/sample"),
    poolsize(0.0F),
    buffersize(100.0F)
{
}

Config::Config(const string& config_path):
	config_path(config_path),
	log_level(logging::trivial::trace),
	sample(false),
	data_path("../data"),
	sample_outpath("../data/sample"),
    poolsize(0.0F),
    buffersize(100.0F)
{
    init(config_path);
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
	this->sample_outpath= config.sample_outpath;
    this->poolsize = config.poolsize;
    this->buffersize = config.buffersize;
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
		this->sample_outpath= config.sample_outpath;
        this->poolsize = config.poolsize;
        this->buffersize = config.buffersize;
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
		os << endl << "\tsample_outpath: " << config.sample_outpath;
        os << endl << "\tpoolsize: " << config.poolsize;
        os << endl << "\tbuffersize: " << config.buffersize;
		os << endl << "}";
	}
    return os;
}


void Config::init(const string& config_path)
{
    //使用Libconfig来加载config
    this->config_path = config_path; //self hold value;

    libconfig::Config mconfig;

    try{
        mconfig.readFile(config_path.c_str());

        double timestep = 3.0F;
		bool sample = false;
        string pathdir;
        string nodedir;
        string loglevel;
		string data_path;
		string sample_outpath;
        double poolsize,buffersize;

        if(mconfig.lookupValue("global.timestep",timestep)){
            this->timestep = timestep;
        }
        if(mconfig.lookupValue("global.sample",sample)){
            this->sample= sample;
        }
        if(mconfig.lookupValue("global.pathdir",pathdir)){
            this->pathdir = pathdir;
        }
        if(mconfig.lookupValue("global.nodedir",nodedir)){
            this->nodedir = nodedir;
        }
        if(mconfig.lookupValue("global.loglevel",loglevel)){
            this->log_level = str2enum(loglevel);
        }


        const libconfig::Setting &demands = mconfig.lookup("demands");
        int count = demands.getLength();

        for(int i=0;i<count;++i){
            int linkid,demand;
            if(!demands[i].lookupValue("linkid",linkid) ||
                    !demands[i].lookupValue("demand",demand)){
                std::cerr << "lookup linkid or demand value error!" << std::endl;
            }else{
                this->demands[linkid] = demand;
            }

        }

		const libconfig::Setting& linkids = mconfig.lookup("sample.linkids");
		for(int i=0; i < linkids.getLength(); ++i){
			this->sample_linkids.push_back(linkids[i]);
		}
		const libconfig::Setting& nodeids = mconfig.lookup("sample.nodeids");
		for(int i=0; i < nodeids.getLength(); ++i){
			this->sample_nodeids.push_back(nodeids[i]);
		}

        if(mconfig.lookupValue("sample.data_path",data_path)){
			this->data_path = data_path;
        }

        if(mconfig.lookupValue("sample.out_path",sample_outpath)){
			this->sample_outpath = sample_outpath;
        }

        if(mconfig.lookupValue("sample.poolsize",poolsize)){
			this->poolsize= poolsize;
        }
		
        if(mconfig.lookupValue("sample.buffersize",buffersize)){
			this->buffersize= buffersize;
        }

    }catch(const libconfig::FileIOException &fioex){
        std::cerr << "can't read config file!" << std::endl;
        return;
    }catch(const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at" << pex.getFile() << ":" << pex.getLine()
                  << "-" << pex.getError() << std::endl;
        return;
    }
}
