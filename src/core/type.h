#ifndef __TYPE_H__
#define __TYPE_H__
//定义基本的类型
#include <string>
#include <sstream>
#include <boost/log/core.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/mutable_constant.hpp>

#include "../utils/tool.hpp"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs    = boost::log::attributes;

extern enum logging::trivial::severity_level str2enum(const std::string& loglevel);
extern void initlog(logging::trivial::severity_level severity);

//macro for log
#define LOG_TRACE(msg)  BOOST_LOG_TRIVIAL(trace) << msg;
#define LOG_DEBUG(msg)  BOOST_LOG_TRIVIAL(debug) << msg;
#define LOG_INFO(msg)   BOOST_LOG_TRIVIAL(info) << msg;
#define LOG_WARNING(msg){\
    BOOST_LOG_FUNCTION();\
    BOOST_LOG_TRIVIAL(warning) <<msg;\
}
#define LOG_ERROR(msg){\
    BOOST_LOG_FUNCTION();\
    BOOST_LOG_TRIVIAL(error) <<msg;\
}
#define LOG_FATAL(msg){\
    BOOST_LOG_FUNCTION();\
    BOOST_LOG_TRIVIAL(fatal) << msg;\
}

//macro for car
#define CARLEN 7.5


enum model_type
{
    FETE = 1,
    CEIL = 2,
    GAWRON = 3,
    TEST = 4,
    DB = 5
};
extern enum model_type str2type(const std::string& type);

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif
