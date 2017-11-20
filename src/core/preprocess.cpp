#include "preprocess.h"
#include "type.h"

#include <string>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;

bool cmp(std::string const &arg_a, std::string const &arg_b) {
	    return arg_a.size() < arg_b.size() || (arg_a.size() == arg_b.size() && arg_a < arg_b);
}

PProcess::PProcess(const string& inpath, const string& pattern,
		const int &interval,const string& outpath, 
		vector<vector<int>>& paths, map<int,Node*>& nodes):
	inpath(inpath),
	pattern(pattern),
	interval(interval),
	outpath(outpath),
    paths(paths),
	nodes(nodes){ 
}

vector<string> PProcess::getFilelist(const string& dirpath,const string& pattern){
	vector<string> filelist;
	if(bf::exists(dirpath)){
		if(bf::is_directory(dirpath)){
			for(auto&& x : bf::directory_iterator(dirpath)){
				//string filename = x.path().filename().string();
				string filename = x.path().string();
				if(filename.find(pattern) != string::npos) 
					filelist.push_back(filename); 
			}
		}
	}
	else{
		LOG_FATAL("data is not exits!!!");
		exit(0);
	}

	sort(filelist.begin(),filelist.end(),cmp);
	return filelist;
}

void PProcess::sampleByTime(const string& path){
	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		while(std::getline(fin,line)){
			int frame,num;
			istringstream is(line);
			is >> frame >> num;

            int carid,type,linkid;
            double x,y,zh;
			for(int i = 0; i < num; ++i){
				std::getline(fin,line);
                istringstream is(line);
                is >> carid >> x >> y >> type >> linkid >> zh;
                //LOG_TRACE(my2string("carid:",carid,"\tposx: ",x,"\tposy: ",y));
                if(magent.find(carid) == magent.end()){
                    magent[carid] = new Agent(carid, linkid);
					mslink[linkid]->inflow++;
					mslink[linkid]->poolnum++;
                }
                else{
                    if(magent[carid]->linkid != linkid){
                        //换道了
                        int pre_linkid = magent[carid]->linkid;
                        mslink[pre_linkid]->outflow++;
                        mslink[pre_linkid]->poolnum--;

                        mslink[linkid]->inflow++;
                        mslink[linkid]->poolnum++;

                        magent[carid]->linkid = linkid;
                    } 
                }
            }

            if(frame % interval == 0){
                //write to file
				//LOG_TRACE(my2string("frame:",frame, " num:" ,num));
                ofstream ofile;
                string outfile = outpath + "/sample.txt";
                ofile.open(outfile.c_str(),std::ios::app);
                ofile << frame << endl;
                for(auto slink : mslink){
                   ofile << slink.first << " " << slink.second->inflow << " " << slink.second->outflow
                        << " " << slink.second->poolnum << endl;
                }
                ofile.close();
            }
		}
	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::sampleByLink(const string& path,const int& link_id){
	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		while(std::getline(fin,line)){
			int frame,num;
			istringstream is(line);
			is >> frame >> num;

            int carid,type,linkid,pathid;
            double x,y,zh;
			for(int i = 0; i < num; ++i){
				std::getline(fin,line);
                istringstream is(line);
                is >> carid >> x >> y >> type >> linkid >> zh;
                //LOG_TRACE(my2string("carid:",carid,"\tposx: ",x,"\tposy: ",y));
                if(magent.find(carid) == magent.end()){
                    magent[carid] = new Agent(carid, linkid);
					mslink[linkid]->inflow++;
					mslink[linkid]->poolnum++;
                }
                else{
                    if(magent[carid]->linkid != linkid){
                        //换道了
                        int pre_linkid = magent[carid]->linkid;
                        mslink[pre_linkid]->outflow++;
                        mslink[pre_linkid]->poolnum--;

                        mslink[linkid]->inflow++;
                        mslink[linkid]->poolnum++;

                        magent[carid]->linkid = linkid;
                    } 
                }
            }

            if(frame % interval == 0){
                //write to file
				//LOG_TRACE(my2string("frame:",frame, " num:" ,num));
                ofstream ofile;
                string outfile = outpath + "/" + std::to_string(link_id)+"_sample.txt";
                ofile.open(outfile.c_str(),std::ios::app);
				auto slink = mslink[link_id];
			    ofile <<  frame << " " << slink->inflow << " " << slink->outflow << " " << slink->poolnum << endl;
                ofile.close();
            }
		}
	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::sampleByNode(const string& path,const int& node_id){

	vector<int> flinks = nodes[node_id]->flinks;
	vector<int> tlinks = nodes[node_id]->tlinks;

	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		while(std::getline(fin,line)){
			int frame,num;
			istringstream is(line);
			is >> frame >> num;

            int carid,type,linkid,pathid;
            double x,y,zh;
			for(int i = 0; i < num; ++i){
				std::getline(fin,line);
                istringstream is(line);
                is >> carid >> x >> y >> type >> linkid >> zh;
                //LOG_TRACE(my2string("carid:",carid,"\tposx: ",x,"\tposy: ",y));
                if(magent.find(carid) == magent.end()){
                    magent[carid] = new Agent(carid, linkid);
					mslink[linkid]->inflow++;
					mslink[linkid]->poolnum++;
                }
                else{
                    if(magent[carid]->linkid != linkid){
                        //换道了
                        int pre_linkid = magent[carid]->linkid;
                        mslink[pre_linkid]->outflow++;
                        mslink[pre_linkid]->poolnum--;

                        mslink[linkid]->inflow++;
                        mslink[linkid]->poolnum++;

                        magent[carid]->linkid = linkid;
                    } 
                }
            }

			//根据node的前后link进行采样
			//格式
			//汇入的link数，每个的poolnum、outflow，下游的link的inflow，poolnum
            if(frame % interval == 0){

				ofstream ofile;
				string outfile = outpath + "/" + std::to_string(node_id) + "_node_sample.txt";
				ofile.open(outfile.c_str(),std::ios::app);

				ofile << frame;
				for(auto link_id : flinks){
					auto slink = mslink[link_id];
					ofile << " " << slink->poolnum << " " << slink->outflow;
				}

				for(auto link_id : tlinks){
					auto slink = mslink[link_id];
					ofile << " " << slink->poolnum << " " << slink->outflow;
				}

				ofile << endl;
				ofile.flush();
				ofile.close();
            }
		}
	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::init(){
    //初始化填充Link
    for(auto path: paths){
        for(auto linkid : path){
            if(mslink.find(linkid) == mslink.end()){
                mslink[linkid] = new Link();
            }
        }
    }
}

void PProcess::doSampleByTime(){
	vector<string> filelist = getFilelist(inpath,pattern);
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		sampleByTime(filename);
	}
}

void PProcess::doSampleByLink(int linkid){
	vector<string> filelist = getFilelist(inpath,pattern);
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		sampleByLink(filename,linkid);
	}
}

void PProcess::doSampleByNode(int nodeid){
	vector<string> filelist = getFilelist(inpath,pattern);
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		sampleByNode(filename,nodeid);
	}
}
