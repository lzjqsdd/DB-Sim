#ifndef __LINK_H__
#define __LINK_H__

#include "agent.h"

#include <stdint.h>
#include <queue>
#include <set>
using namespace std;


/****************************************/
struct cmp{
	bool operator()(Agent *a, Agent*b){
		return a->arrival_time < b->arrival_time;
	}
};

class Agent;
class Link{
public:
    Link();
    Link(const Link& link);
    Link(int32_t id , double length , double maxspeed, int poolnum);
    Link& operator=(const Link& link);

    ~Link();

    int32_t id;
	set<int32_t> nids; //next link ids
	set<int32_t> pids; //previous link ids
    double length; //length of link
    double maxspeed; //max speed limit
    double lane_num; //count of lanes
    double capacity; //count of outflow per unit
    double poolnum;
    double totalnum; //总可以容纳的车辆数
    double buffernum;
    priority_queue<Agent*, vector<Agent *>,  cmp> wait_queue;


    //for data sampling
    double inflow;
    double outflow;
};

#endif 
