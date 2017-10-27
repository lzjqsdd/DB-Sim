#include "node.h"

Node::Node(){
    //default;
}

Node::Node(const Node& node){
    nid = node.nid;
}

Node& Node::operator=(const Node& node){
    nid = node.nid;
}
