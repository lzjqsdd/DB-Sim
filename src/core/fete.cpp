#include "fete.h"

FETE::FETE(){
    
}

FETE::FETE(const Config &config){ 
    _config = config;
}

FETE& FETE::operator=(const FETE& fete){
    
}


/**********************************/


void FETE::loadNetwork(){
    //加载links和nodes
    _manager->loadLinks(_config.pathdir, links);
    _manager->loadNodes(_config.nodedir, nodes);
}

void FETE::init(){
    //加载路网
    loadNetwork();
}

Config FETE::getConfig(){
    return _config;
} 

void FETE::doUpdate(){ 

}
void FETE::start(){

}
void FETE::check(){

}

