#ifndef __AGENT_H__
#define __AGENT_H__

#include <utility>
#include <stdint.h>
using namespace std;

class Agent{
    public:
        Agent();
        Agent(int id, int linkid);
        Agent(const Agent& agent);
        Agent& operator=(const Agent& agent);
        ~Agent();
        bool operator<(const Agent& agent) const{
            return agent.arrival_time < arrival_time;
        }

        int32_t id;
        int32_t linkid; //the agent on which link
        double cur_speed; //show per time step the agent speed
        double type; //different agent type
        double length; //car length
        int arrival_time; //the time when arrival the link end
};

#endif
