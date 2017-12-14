#include "bfete.h"

#include "../utils/tinyxml2.h"
#include "../utils/tool.hpp"
#include "../core/type.h"

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/filesystem.hpp>

using namespace tinyxml2;
using namespace boost::algorithm;
namespace logging = boost::log;
namespace bf = boost::filesystem;

void FETEIf::loadLinks(map<int, shared_ptr<Link>>& links, vector<vector<int>>& paths){
    //����path.xml���links
    //load config
    
    if(!bf::exists(_config.pathdir)){
        LOG_TRACE("path.xmlnot found!");
        exit(0);
    }

    XMLDocument doc;
    doc.LoadFile(_config.pathdir.c_str());
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
            totalnum = length * 1 / CARLEN; //ÿ����7.5��,Ĭ�϶��ǣ���lane

            LOG_TRACE(my2string("linkid is :" ,id , ", length is : " , lengthNode->Value() , ", maxspeed is: " , speedNode->Value() , ", totalnum is: " , totalnum));

            shared_ptr<Link> mlink = shared_ptr<Link>(new Link(id,length,maxspeed,totalnum));
            links[id] = mlink;
            path.push_back(id);

            linkElement = linkElement->NextSiblingElement();
        }
        paths.push_back(path);
        pathElement = pathElement->NextSiblingElement();
    }
}

void FETEIf::loadNodes(map<int, shared_ptr<Node>>& nodes){
    //����node.xml���nodes
    if(!bf::exists(_config.nodedir)){
        LOG_TRACE("node.xml not found!");
        exit(0);
    }
    XMLDocument doc;
    doc.LoadFile(_config.nodedir.c_str());

    XMLElement * nodesElement = doc.FirstChildElement("nodes");
    XMLElement * nodeElement = nodesElement->FirstChildElement("node");

    while(nodeElement){
        int id;
        vector<int> flinks; //�洢���ǻ���link�ı��
        vector<int> tlinks; //����link�ı��

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

        shared_ptr<Node> pnode = shared_ptr<Node>(new Node(id, flinks_id, tlinks_id));
        nodes[id] = pnode;

        nodeElement = nodeElement->NextSiblingElement();
    }
}

void FETEIf::fillLinks(const vector<vector<int>>& paths , map<int, shared_ptr<Link>>& links){
	//����path�е�ÿ��link��������link��ǰ���ϵ
	for(auto path : paths){
		for(int i = 1; i<path.size(); ++i){
			int32_t pid = path[i-1];
			int32_t cid = path[i];
			links[pid]->nids.insert(cid);
			links[cid]->pids.insert(pid);
		}
	}
}
