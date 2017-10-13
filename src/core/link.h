#ifndef __LINK_H__
#define __LINK_H__

#include "agent.h"

#include <queue>
using namespace std;

class Link{
public:
    Link(){}
    ~Link(){}

private:
    int32_t lid;
    double length; //length of link
    double lane_num; //count of lanes
    double capacity; //count of outflow per unit
    priority_queue<Agent> wait_queue;
    
};

#endif 
