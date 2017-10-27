#include "link.h"

Link::Link(){
    //default
}

Link::Link(const Link& link){
    id = link.id;
    length = link.length;
    lane_num = link.lane_num;
    capacity = link.capacity;
    wait_queue = link.wait_queue;
}

Link& Link::Link(const Link& link){
    if(this != &link){
        id = link.id;
        length = link.length;
        lane_num = link.lane_num;
        capacity = link.capacity;
        wait_queue = link.wait_queue;
    }
    return *this;
}
