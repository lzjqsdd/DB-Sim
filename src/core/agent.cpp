#include "agent.h"


Agent::Agent(){
    //default
}


Agent::Agent(const Agent& agent){
    id = agent.id;
    linkid = agent.id;
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