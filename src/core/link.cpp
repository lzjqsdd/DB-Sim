#include "link.h"

Link::Link(){
    //default
    id = 0;
    length = 0;
    maxspeed = 0;
    lane_num = 0;
    capacity = 0;
    poolnum  = 0;
}


Link::Link(int32_t id , double length , double maxspeed, int totalnum){
    id = id;
    length = length;
    maxspeed = maxspeed;
    lane_num = 1; //defalut value
    capacity = 100;
    totalnum = totalnum;
}

Link::Link(const Link& link){
    id = link.id;
    length = link.length;
    maxspeed = link.maxspeed;
    lane_num = link.lane_num;
    capacity = link.capacity;
    wait_queue = link.wait_queue;
    poolnum = link.poolnum;
    totalnum = link.totalnum;
}

Link& Link::operator=(const Link& link){
    if(this != &link){
        id = link.id;
        length = link.length;
        maxspeed = link.maxspeed;
        lane_num = link.lane_num;
        capacity = link.capacity;
        wait_queue = link.wait_queue;
        poolnum = link.poolnum;
        totalnum = link.totalnum;
    }
    return *this;
}

Link::~Link(){
    
}