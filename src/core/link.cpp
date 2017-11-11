#include "link.h"

Link::Link(){
    //default
    id = 0;
    length = 0;
    maxspeed = 0;
    lane_num = 0;
    capacity = 0;
}


Link::Link(int32_t id , double length , double maxspeed, int poolnum){
    id = id;
    length = length;
    maxspeed = maxspeed;
    lane_num = 1; //defalut value
    capacity = 100;
    poolnum = poolnum;
}

Link::Link(const Link& link){
    id = link.id;
    length = link.length;
    maxspeed = link.maxspeed;
    lane_num = link.lane_num;
    capacity = link.capacity;
    wait_queue = link.wait_queue;
}

Link& Link::operator=(const Link& link){
    if(this != &link){
        id = link.id;
        length = link.length;
        maxspeed = link.maxspeed;
        lane_num = link.lane_num;
        capacity = link.capacity;
        wait_queue = link.wait_queue;
    }
    return *this;
}

Link::~Link(){
    
}