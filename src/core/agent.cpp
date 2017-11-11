#include "agent.h"


Agent::Agent(){
    //default
}

Agent::Agent(int id, int linkid){
    id = id;
    linkid = linkid;
    cur_speed = 0;
    type = 0;
    length = 3;
    arrival_time = 0;
}

Agent::Agent(const Agent& agent){
    id = agent.id;
    linkid = agent.linkid;
    cur_speed = agent.cur_speed;
    type = agent.type;
    length = agent.length;
    arrival_time = agent.arrival_time;
}

Agent& Agent::operator=(const Agent& agent){
    if(this != &agent){
        id = agent.id;
        linkid = agent.id;
        cur_speed = agent.cur_speed;
        type = agent.type;
        length = agent.length;
        arrival_time = agent.arrival_time;
    }
    return *this;
}

Agent::~Agent(){
    
}
