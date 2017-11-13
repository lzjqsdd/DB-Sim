#ifndef __TYPE_H__
#define __TYPE_H__
//定义基本的类型
#include <string>
#include <sstream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
namespace logging = boost::log;

extern enum logging::trivial::severity_level str2enum(const std::string& loglevel);
extern void initlog(logging::trivial::severity_level severity);


//macro for log
#define LOG_TRACE(msg) BOOST_LOG_TRIVIAL(trace) << msg;
#define LOG_DEBUG(msg) BOOST_LOG_TRIVIAL(debug) << msg;
#define LOG_INFO(msg) BOOST_LOG_TRIVIAL(info) << msg;
#define LOG_WARNING(msg) BOOST_LOG_TRIVIAL(warning) << msg;
#define LOG_ERROR(msg) BOOST_LOG_TRIVIAL(error) << msg;
#define LOG_FATAL(msg) BOOST_LOG_TRIVIAL(fatal) << msg;

//macro for car
#define CARLEN 7.5

#endif
