#ifndef __LINK_H__
#define __LINK_H__

#include "agent.h"

#include <stdint.h>
#include <queue>
using namespace std;

class Agent;
class Link{
public:
    Link();
    Link(const Link& link);
    Link(int32_t id , double length , double maxspeed);
    Link& operator=(const Link& link);

    ~Link();

private:
    int32_t id;
    double length; //length of link
    double maxspeed; //max speed limit
    double lane_num; //count of lanes
    double capacity; //count of outflow per unit
    double poolnum;
    double buffernum;
    priority_queue<Agent> wait_queue;
};

#endif 
