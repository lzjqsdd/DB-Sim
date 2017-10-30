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

int main()
{
    cout << "FETE starting ..." << endl;

    FETE fete; //主要处理类
    fete.init();
    //load config
    //build network
    //init evacuation demand
    //do simulation per step
    //calc time
}
