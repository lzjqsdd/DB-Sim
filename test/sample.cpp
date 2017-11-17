#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/filesystem.hpp>
using namespace std;
namespace bf = boost::filesystem;


void readFile(const string&path)
{
	fstream fin(path.c_str(),std::ifstream::in);
	string line;
	while(std::getline(fin,line)){
		int frame,num;
		istringstream is(line);
		is >> frame >> num;
		cout << "frame:" << frame << " num:" << num << endl;

		for(int i = 0; i < num; ++i)
			std::getline(fin,line);
	}
}

//查找.txt后缀的文件
vector<string> getFilelist(const string& dirpath,const string &pattern)
{
	vector<string> filelist;
	if(bf::exists(dirpath)){
		cout << "dirpath exists" << endl;
		if(bf::is_directory(dirpath)){
			for(auto&& x : bf::directory_iterator(dirpath)){
				string filename = x.path().filename().string();
				if(filename.find(pattern) != string::npos) 
					filelist.push_back(filename); 
			}
		}
	}
	for(auto &&x:filelist) cout << x << endl;
	return filelist;
}

int main()
{
	string path = "../data/car1.txt";
	//readFile(path);
	getFilelist("../data/","tra");
}
