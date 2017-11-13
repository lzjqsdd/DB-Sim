#include "node.h"

Node::Node(){
    //default;
}

Node::Node(int id, vector<int> flinks, vector<int>tlinks):
	id(id), flinks(flinks), tlinks(tlinks), isOrigin(false){
}

Node::Node(const Node& node){
    this->id = node.id;
    this->flinks = node.flinks;
    this->tlinks = node.tlinks;
    this->isOrigin = node.isOrigin;
}

Node& Node::operator=(const Node& node){
    this->id = node.id;
    this->flinks = node.flinks;
    this->tlinks = node.tlinks;
    this->isOrigin = node.isOrigin;
}

Node::~Node(){
    
}
