#include "type.h"

#include <sstream>
//提供从str到枚举的转换
enum logging::trivial::severity_level str2enum(const std::string& loglevel)
{
   if(loglevel == "trace") return logging::trivial::trace;
   else if(loglevel == "debug") return logging::trivial::debug;
   else if(loglevel == "info") return logging::trivial::info;
   else if(loglevel == "warning") return logging::trivial::warning;
   else if(loglevel == "error") return logging::trivial::error;
   else if(loglevel == "fatal_log") return logging::trivial::fatal;
   return logging::trivial::trace;
}

void initlog(logging::trivial::severity_level severity)
{
    logging::add_file_log(
		keywords::file_name="fete_%N.log",
		keywords::rotation_size=10*1024*1024,
        keywords::format = 
        (
            expr::stream
                << "[" << boost::log::trivial::severity << "] "
                << boost::log::expressions::smessage
        )
    );

    logging::add_console_log(
        std::cout,
        boost::log::keywords::format = 
        (
            expr::stream
                << "[" << boost::log::trivial::severity << "] "
                << boost::log::expressions::smessage
        )
    );

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= severity
    );
}

