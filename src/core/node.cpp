#include "node.h"

Node::Node(){
    //default;
}

Node::Node(int id, vector<int> flinks, vector<int>tlinks){
    id = id;
    flinks = flinks;
    tlinks = tlinks;
}

Node::Node(const Node& node){
    id = node.id;
}

Node& Node::operator=(const Node& node){
    id = node.id;
}

Node::~Node(){
    
}