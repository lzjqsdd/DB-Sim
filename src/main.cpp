#include <iostream>
#include <cstdio>

#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"
#include "./core/fete.h"

#include "./utils/tinyxml2.h"
#include "./utils/manager.h"

using namespace std;
using namespace tinyxml2;


//初始化数据
void init(){

}


//加载Paths
void LoadPath(){

}

//加载Nodes
void LoadNodes(){

}


int main()
{
    cout << "FETE starting ..." << endl;

    FETE fete;
    fete.init();
    //load config
    //build network
    //init evacuation demand
    //do simulation per step
    //calc time
}
