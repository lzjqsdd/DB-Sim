#include "manager.h"
#include "../utils/tinyxml2.h"
#include "../utils/tool.hpp"
#include "../core/type.h"

#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>

#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

using namespace tinyxml2;
using namespace boost::algorithm;
namespace logging = boost::log;

Manager * Manager::_manager = new Manager();

Manager::Manager(){
}

Manager * Manager::getManager(){
    return _manager;
}


//gconfig: global config
void Manager::loadConfig(const string&path, Config& gconfig){
    //使用Libconfig来加载config
    gconfig.config_path = path; //self hold value;

    libconfig::Config mconfig;

    try{
        mconfig.readFile(path.c_str());

        double timestep = 3.0F;
        string pathdir;
        string nodedir;
        string loglevel;
        if(mconfig.lookupValue("global.timestep",timestep)){
            gconfig.timestep = timestep;
        }
        if(mconfig.lookupValue("global.pathdir",pathdir)){
            gconfig.pathdir = pathdir;
        }
        if(mconfig.lookupValue("global.nodedir",nodedir)){
            gconfig.nodedir = nodedir;
        }
        if(mconfig.lookupValue("global.loglevel",loglevel)){
            gconfig.log_level = str2enum(loglevel);
        }

        const libconfig::Setting &demands = mconfig.lookup("demands");
        int count = demands.getLength();

        for(int i=0;i<count;++i){
            int linkid,demand;
            if(!demands[i].lookupValue("linkid",linkid) ||
                    !demands[i].lookupValue("demand",demand)){
                std::cerr << "lookup linkid or demand value error!" << std::endl;
            }else{
                gconfig.demands[linkid] = demand;
            }

        }

    }catch(const libconfig::FileIOException &fioex){
        std::cerr << "can't read config file!" << std::endl;
        return;
    }
    catch(const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at" << pex.getFile() << ":" << pex.getLine()
                  << "-" << pex.getError() << std::endl;
        return;
    }
}

void Manager::loadLinks(const string& filepath, map<int, Link*>& links, vector<vector<int>>& paths){
    //遍历path.xml填充links
    //load config
    XMLDocument doc;
    doc.LoadFile("../config/path.xml");
    XMLElement * pathListElement = doc.FirstChildElement("pathlist");
    XMLElement * pathElement= pathListElement->FirstChildElement("path");

    while(pathElement){
        XMLElement *linkElement = pathElement->FirstChildElement("link");
        vector<int> path;
        while(linkElement){
            int id,totalnum;
            double length,maxspeed;
            linkElement->QueryAttribute("id",&id);
            XMLElement *speedElement = linkElement->FirstChildElement("maxspeed");
            XMLElement *lengthElement = linkElement->FirstChildElement("length");
            XMLText* speedNode = speedElement->FirstChild()->ToText();
            XMLText* lengthNode = lengthElement->FirstChild()->ToText();

            length = atof(lengthNode->Value());
            maxspeed = atof(speedNode->Value());
            totalnum = length * 1 / CARLEN; //每个车7.5米,默认都是１个lane

            LOG_TRACE(my2string("linkid is :" ,id , ", length is : " , lengthNode->Value() , ", maxspeed is: " , speedNode->Value() , ", totalnum is: " , totalnum));

            Link* mlink = new Link(id,length,maxspeed,totalnum);
            links[id] = mlink;
            path.push_back(id);

            linkElement = linkElement->NextSiblingElement();
        }
        paths.push_back(path);
        pathElement = pathElement->NextSiblingElement();
    }
}

void Manager::loadNodes(const string& path, map<int, Node*>& nodes){
    //遍历node.xml填充nodes
    XMLDocument doc;
    doc.LoadFile(path.c_str());

    XMLElement * nodesElement = doc.FirstChildElement("nodes");
    XMLElement * nodeElement = nodesElement->FirstChildElement("node");

    while(nodeElement){
        int id;
        vector<int> flinks; //存储的是汇入link的编号
        vector<int> tlinks; //流出link的编号

        nodeElement->QueryAttribute("id", &id);
        XMLElement * flinksElement = nodeElement->FirstChildElement("flinks");
        XMLElement * tlinksElement = nodeElement->FirstChildElement("tlinks");
        
        string flinks_s,tlinks_s;
        if(!flinksElement->NoChildren()) flinks_s = flinksElement->GetText();
        if(!tlinksElement->NoChildren()) tlinks_s = tlinksElement->GetText();
        vector<string> flinks_v,tlinks_v;
        if(flinks_s!="") split(flinks_v, flinks_s , is_any_of(" "));
        if(tlinks_s!="") split(tlinks_v, tlinks_s , is_any_of(" "));

        vector<int> flinks_id, tlinks_id;
        for(vector<string>::iterator it = flinks_v.begin();it!=flinks_v.end();++it) flinks_id.push_back(boost::lexical_cast<int>(*it));
        for(vector<string>::iterator it = tlinks_v.begin();it!=tlinks_v.end();++it) tlinks_id.push_back(boost::lexical_cast<int>(*it));

        Node * pnode = new Node(id, flinks_id, tlinks_id);
        nodes[id] = pnode;

        nodeElement = nodeElement->NextSiblingElement();
    }
}

void Manager::fillLinks(const vector<vector<int>>& paths , map<int, Link*>& links){
	//遍历path中的每个link，来处理link的前后关系
	for(auto path : paths){
		for(int i = 1; i<path.size(); ++i){
			int32_t pid = path[i-1];
			int32_t cid = path[i];
			links[pid]->nids.insert(cid);
			links[cid]->pids.insert(pid);
		}
	}
}
