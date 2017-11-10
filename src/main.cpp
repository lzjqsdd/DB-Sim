#include <iostream>
#include <cstdio>

#include "./core/type.h"
#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"
#include "./core/fete.h"

#include "./utils/tinyxml2.h"
#include "./core/manager.h"

using namespace std;
using namespace tinyxml2;

int main()
{
    //加载配置文件
    Config config;
    Manager * manager = Manager::getManager();
    manager->loadConfig("../config/config.conf",config);
    cout << config << endl;

    initlog(config.log_level);
    //创建推演对象
    FETE fete(config); //主要处理类
    fete.init();
    fete.start();
}
