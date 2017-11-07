#include "fete.h"

FETE::FETE(){
    
}

FETE::FETE(const Config &config){ 

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
    //加载配置文件
    _manager = Manager::getManager();
    _manager->loadConfig("../config/config.conf",_config);
    cout << "Timestep is " << _config.timestep << endl;
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

