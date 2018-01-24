#include "link.h"
#include "type.h"

Link::Link():
    //default
    id (0),
    length(0),
    maxspeed(0),
    lane_num(0),
    capacity(0),
    poolnum (0),
    buffernum(0),
    inflow(0),
    outflow(0),
    sum_frame(0),
    sum_zh(0),
    avg_speed(0),
    pool_zh(0),
    buffer_zh(0),
    pool2buffer(0.0F){
}


Link::Link(int32_t id , double length , double maxspeed, int totalnum,
        double pool_zh , double buffer_zh):
	id(id),length(length),maxspeed(maxspeed),lane_num(1),
	capacity(100),totalnum(totalnum),poolnum(0),buffernum(0),
	inflow(0),outflow(0),
    sum_frame(0),sum_zh(0), avg_speed(0),
    pool_zh(pool_zh), buffer_zh(buffer_zh),
    pool2buffer(pool2buffer){ 
}


Link::Link(const Link& link){
    this->id = link.id;
    this->length = link.length;
    this->maxspeed = link.maxspeed;
    this->lane_num = link.lane_num;
    this->capacity = link.capacity;
    this->wait_queue = link.wait_queue;
    this->poolnum = link.poolnum;
    this->buffernum= link.buffernum;
    this->totalnum = link.totalnum;
    
    this->sum_frame = link.sum_frame;
    this->sum_zh = link.sum_zh;
    this->avg_speed = link.avg_speed;

    this->pool_zh = link.pool_zh;
    this->buffer_zh = link.buffer_zh;
    this->pool2buffer = link.pool2buffer;
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
        this->buffernum= link.buffernum;
        this->totalnum = link.totalnum;

        this->sum_frame = link.sum_frame;
        this->sum_zh = link.sum_zh;
        this->avg_speed = link.avg_speed;

        this->pool_zh = link.pool_zh;
        this->buffer_zh = link.buffer_zh;
        this->pool2buffer = link.pool2buffer;
    }
    return *this;
}
ostream& operator<<(ostream& os, const Link& link){
    os  << BOLDBLUE << "[" <<  std::right<< setw(4) << std::setfill(' ') << link.poolnum
        <<  "|" << std::left<< setw(4) << std::setfill(' ') << link.buffernum <<"]" << RESET;
    return os;

}

Link::~Link(){
    
}

