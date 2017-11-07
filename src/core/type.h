#ifndef __TYPE_H__
#define __TYPE_H__
//定义基本的类型
#include <string>
#include <boost/log/trivial.hpp>

using namespace std;
namespace logging = boost::log;

extern enum logging::trivial::severity_level str2enum(const string& loglevel);
#endif
