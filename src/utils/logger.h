#ifndef __LOG__H
#define __LOG__H

#include <boost/thread.hpp>

class Logger{
    public:
        static Logger& getLogger();
    protected:
};

#endif
