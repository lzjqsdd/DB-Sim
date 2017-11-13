#include "link.h"

Link::Link(){
    //default
    this->id = 0;
    this->length = 0;
    this->maxspeed = 0;
    this->lane_num = 0;
    this->capacity = 0;
    this->poolnum  = 0;
}


Link::Link(int32_t id , double length , double maxspeed, int totalnum):
	id(id),length(length),maxspeed(maxspeed),lane_num(1),
	capacity(100),totalnum(totalnum),poolnum(0) { 
}

Link::Link(const Link& link){
    this->id = link.id;
    this->length = link.length;
    this->maxspeed = link.maxspeed;
    this->lane_num = link.lane_num;
    this->capacity = link.capacity;
    this->wait_queue = link.wait_queue;
    this->poolnum = link.poolnum;
    this->totalnum = link.totalnum;
}

Link& Link::operator=(const Link& link){
    if(this != &link){
        this->id = link.id;
        this->length = link.length;
        this->maxspeed = link.maxspeed;
        this->lane_num = link.lane_num;
        this->capacity = link.capacity;
        this->wait_queue = link.wait_queue;
        this->poolnum = link.poolnum;
        this->totalnum = link.totalnum;
    }
    return *this;
}

Link::~Link(){
    
}
