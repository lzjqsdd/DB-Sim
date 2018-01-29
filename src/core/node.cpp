#include "node.h"
#include "type.h"

Node::Node(){
    //default;
}

Node::Node(int id, vector<int> flinks, vector<int>tlinks, float capacity):
	id(id), flinks(flinks), tlinks(tlinks), isOrigin(false),
    inflow(0.0F),
    capacity(capacity){
}


Node::Node(const Node& node){
    this->id = node.id;
    this->flinks = node.flinks;
    this->tlinks = node.tlinks;
    this->isOrigin = node.isOrigin;
    this->inflow = node.inflow;
    this->capacity = node.capacity;
}

Node& Node::operator=(const Node& node){
    this->id = node.id;
    this->flinks = node.flinks;
    this->tlinks = node.tlinks;
    this->isOrigin = node.isOrigin;
    this->inflow = node.inflow;
    this->capacity = node.capacity;
}

Node::~Node(){
    
}

ostream& operator<<(ostream& os, const Node& node){
    os << "⟮-•" << BOLDYELLOW << "(" <<  node.inflow << ")" << RESET << "•→ ";
    return os;
}

