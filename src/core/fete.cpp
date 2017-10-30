#include "fete.h"

FETE::FETE(){
    
}

FETE::FETE(const Config &config){ 

}

FETE& FETE::operator=(const FETE& fete){
    
}


/**********************************/


void FETE::loadNetwork(){
    //先得到config
    _manager = Manager::getManager();

    //加载配置文件
    _manager->loadConfig("../config/config.conf",_config);
    cout << "Timestep is " << _config.timestep << endl;

    //加载links
    _manager->loadLinks(_config.pathdir, links);
    _manager->loadNodes(_config.nodedir, nodes);
}

void FETE::init(){
    loadNetwork();
}
void FETE::doUpdate(){
    
}
void FETE::start(){

}
void FETE::check(){

}

