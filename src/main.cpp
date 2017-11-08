#include <iostream>
#include <cstdio>

#include "./core/agent.h"
#include "./core/link.h"
#include "./core/node.h"
#include "./core/config.h"
#include "./core/fete.h"

#include "./utils/tinyxml2.h"
#include "./core/manager.h"
#include "./utils/simpleLogger.h"

using namespace std;
using namespace tinyxml2;


/**
 * 初始化log等级
 */
//void init(const Config& config){
//    logging::core::get()->set_filter(
//            logging::trivial::severity >= config.log_level
//    );
//    //Test log filter
//    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
//    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
//    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
//    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
//    BOOST_LOG_TRIVIAL(error) << "An error severity message";
//    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
//}
//




int main()
{
    FETE fete; //主要处理类
    fete.init();
    Config cur_config = fete.getConfig();

    LOG_TRACE << "trace ...";
    LOG_DEBUG << "DEBUG ...";
    LOG_INFO  << "info ...";



    //load config
    //build network
    //init evacuation demand
    //do simulation per step
    //calc time
}
