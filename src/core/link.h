#ifndef __LINK_H__
#define __LINK_H__

#include "agent.h"

#include <stdint.h>
#include <queue>
#include <set>
#include <memory>
using namespace std;


/****************************************/
struct cmp{
	bool operator()(shared_ptr<Agent> a, shared_ptr<Agent> b){
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
    priority_queue<shared_ptr<Agent>, vector<shared_ptr<Agent>>,  cmp> wait_queue;


    //for data sampling
    double inflow;
    double outflow;
    double sum_frame;  //统计累积总时间
    double sum_zh; //统计区间累积总里程
    double avg_speed;
};

#endif 
