#include "node.h"

Node::Node(){
    //default;
}

Node::Node(int id, vector<int> flinks, vector<int>tlinks){
    id = id;
    flinks = flinks;
    tlinks = tlinks;
    isOrigin = false;
}

Node::Node(const Node& node){
    id = node.id;
    flinks = node.flinks;
    tlinks = node.tlinks;
    isOrigin = node.isOrigin;
}

Node& Node::operator=(const Node& node){
    id = node.id;
    flinks = node.flinks;
    tlinks = node.tlinks;
    isOrigin = node.isOrigin;
}

Node::~Node(){
    
}