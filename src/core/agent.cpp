#include "agent.h"
#include "type.h"


Agent::Agent(){
    //default
}

Agent::Agent(int id, int linkid):
	id(id), linkid(linkid) , cur_speed(0),
	type(0), length(CARLEN), arrival_time(0){
}

Agent::Agent(const Agent& agent){
    this->id = agent.id;
    this->linkid = agent.linkid;
    this->cur_speed = agent.cur_speed;
    this->type = agent.type;
    this->length = agent.length;
    this->arrival_time = agent.arrival_time;
}

Agent& Agent::operator=(const Agent& agent){
    if(this != &agent){
        this->id = agent.id;
        this->linkid = agent.id;
        this->cur_speed = agent.cur_speed;
        this->type = agent.type;
        this->length = agent.length;
        this->arrival_time = agent.arrival_time;
    }
    return *this;
}

Agent::~Agent(){
    
}
