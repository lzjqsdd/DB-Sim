#include "config.h"

Config::Config():
	config_path("../config"),
	log_level(logging::trivial::trace),
	sample(false),
	data_path("../data"),
    data_prefix("car"),
	sample_outpath("../data/sample"),
    poolsize(0.0F),
    buffersize(100.0F),
    cleanall(false)
{
}

Config::Config(const string& config_path):
	config_path(config_path),
	log_level(logging::trivial::trace),
	sample(false),
	data_path("../data"),
    data_prefix("car"),
	sample_outpath("../data/sample"),
    poolsize(0.0F),
    buffersize(100.0F),
    cleanall(false)
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
    this->data_prefix = config.data_prefix;
	this->sample_linkids = config.sample_linkids;
	this->sample_nodeids = config.sample_nodeids;
	this->sample_outpath= config.sample_outpath;
    this->poolsize = config.poolsize;
    this->buffersize = config.buffersize;
    this->cleanall = config.cleanall;
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
        this->data_prefix = config.data_prefix;
		this->sample_linkids = config.sample_linkids;
		this->sample_nodeids = config.sample_nodeids;
		this->sample_outpath= config.sample_outpath;
        this->poolsize = config.poolsize;
        this->buffersize = config.buffersize;
        this->cleanall = config.cleanall;
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
        os << endl << "\tcleanAll: " << config.cleanall;
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
        bool cleanall;

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

        if(mconfig.lookupValue("sample.data_prefix",data_path)){
			this->data_prefix= data_prefix;
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

        if(mconfig.lookupValue("sample.cleanall",cleanall)){
            this->cleanall = cleanall;
        }


        //model config
        string xgboost_version;
        if(mconfig.lookupValue("model.xgboost_version",xgboost_version)){
            this->xgboost_version = xgboost_version;
        }

        try{
            const libconfig::Setting& xgboost_model_list = mconfig.lookup("model.xgboost_model_list");
            int model_count = xgboost_model_list.getLength();
            for(int i=0; i< model_count; ++i){
                string cur_version;
                xgboost_model_list[i].lookupValue("model_version",cur_version);

                //查找当前需要的版本
                if(xgboost_version ==  cur_version){
                    xgboost_model_list[i].lookupValue("model_desc",this->xgboost_desc);
                    const libconfig::Setting& model_list = xgboost_model_list[i]["model_list"];
                    //遍历当前版本所有node的model
                    int node_model_count = model_list.getLength();
                    this->xgboost_model.resize(node_model_count);
                    for(int j = 0; j< node_model_count; ++j){
                        //   model_list[j].lookupValue("node_id",this->xgboost_model[j].node_id); 
                        //   model_list[j].lookupValue("model_file",this->xgboost_model[j].model_file);
                        this->xgboost_model[j].node_id = model_list[j]["node_id"];
                        this->xgboost_model[j].model_file = model_list[j]["model_file"].c_str(); //这里使用c_str是因为setting 到 string的转换会出现多个重载可选的情况
                    }
                }

            }

        }catch(const libconfig::SettingNotFoundException &snfex){
            std::cerr << "can't found xgboost_model_list config" << std::endl;
            exit(-1);
        }



    }catch(const libconfig::FileIOException &fioex){
        std::cerr << "can't read config file!" << std::endl;
        exit(-1);
    }catch(const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at" << pex.getFile() << ":" << pex.getLine()
                  << "-" << pex.getError() << std::endl;
        exit(-1);
    }
}
