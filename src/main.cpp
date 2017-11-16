#include <iostream>
#include <cstdio>
#include<sstream>


#include "./core/type.h"
#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"
#include "./core/bfete.h"
#include "./core/cfete.h"
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
    LOG_TRACE(config);

    //初始化日志等级
    initlog(config.log_level);


    //创建推演对象
    CFETE fete(config); //主要处理类
	FETEIf &f = fete;
	f.init();
	f.start();
    //fete.init();
    //fete.start();
}
