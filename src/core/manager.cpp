#include "manager.h"
#include "../utils/tinyxml2.h"
#include "../utils/tool.hpp"
#include "../core/type.h"

#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>

#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

using namespace tinyxml2;
using namespace boost::algorithm;
namespace logging = boost::log;

shared_ptr<Manager> Manager::_manager = shared_ptr<Manager>(new Manager());

Manager::Manager(){
}

shared_ptr<Manager> Manager::getManager(){
    return _manager;
}

void Manager::init(const Config& config){
    _config = config;  
}

shared_ptr<FETEIf> Manager::getTestModel(){
    shared_ptr<FETEIf> test_model = shared_ptr<FETEIf>(new TFETE(_config));
    return test_model;
}

shared_ptr<FETEIf> Manager::getCeilModel(){
    shared_ptr<FETEIf> ceil_model = shared_ptr<FETEIf>(new CFETE(_config));
    return ceil_model;
}

shared_ptr<FETEIf> Manager::getGawronModel(){
    shared_ptr<FETEIf> gawron_model = shared_ptr<FETEIf>(new GFETE(_config));
    return gawron_model;
}

shared_ptr<FETEIf> Manager::getFETEModel(){
    //TODO
    shared_ptr<FETEIf> test_model = shared_ptr<FETEIf>(new TFETE(_config));
    return test_model;
}
