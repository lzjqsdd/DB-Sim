#include "preprocess.h"
#include "type.h"

#include <string>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;

PProcess::PProcess(const string& inpath, const string& pattern,
		const int &interval,const string& outpath):
	inpath(inpath),
	pattern(pattern),
	interval(interval),
	outpath(outpath) { 

}

vector<string> PProcess::getFilelist(const string& dirpath,const string& pattern){
	vector<string> filelist;
	if(bf::exists(dirpath)){
		if(bf::is_directory(dirpath)){
			for(auto&& x : bf::directory_iterator(dirpath)){
				string filename = x.path().filename().string();
				if(filename.find(pattern) != string::npos) 
					filelist.push_back(filename); 
			}
		}
	}
	else{
		LOG_FATAL("data is not exits!!!");
		exit(0);
	}
	return filelist;
}

void PProcess::readFile(const string& path){
	try{
		fstream fin(path.c_str(),std::ifstream::in);
		string line;
		while(std::getline(fin,line)){
			int frame,num;
			istringstream is(line);
			is >> frame >> num;
			LOG_DEBUG(my2string("frame:",frame, " num:" ,num));

			for(int i = 0; i < num; ++i)
				std::getline(fin,line);
		}
	}catch(...){
		LOG_FATAL("can't read file content!!!");
	}
}

void PProcess::doSample(){
	vector<string> filelist = getFilelist(inpath,pattern);
	for(auto filename : filelist){
		LOG_TRACE(my2string("read file: ",filename));
		readFile(filename);
	}
}
