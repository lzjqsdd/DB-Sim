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
   else if(loglevel == "fatal") return logging::trivial::fatal;
   return logging::trivial::trace;
}

void initlog(logging::trivial::severity_level severity)
{


    logging::core::get()->set_filter
    (
        logging::trivial::severity >= severity
    );

    logging::add_file_log(
		keywords::file_name="fete%N.log",
		keywords::rotation_size=10*1024*1024,
        keywords::format = expr::format("[%1%] [%2%] [%3%] %4%") 
            % expr::attr< boost::log::trivial::severity_level>("Severity")
            % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%H:%M:%S") 
            % expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)") 
            % expr::message 
    );

    logging::add_console_log(
        std::cout,
        keywords::format = expr::format("[%1%] [%2%] [%3%] %4%") 
            % expr::attr< boost::log::trivial::severity_level>("Severity")
            % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%H:%M:%S") 
            % expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)") 
            % expr::message 
    );

    logging::add_common_attributes();
    logging::core::get()->add_global_attribute("Scope", attrs::named_scope());

}


enum model_type str2type(const std::string& type){
    if(type == "ceil") return CEIL;
    else if(type == "gawron") return GAWRON;
    else if(type == "fete") return FETE;
    else if(type == "test") return TEST;
    else if(type == "db")   return DB;

    return TEST;
}
