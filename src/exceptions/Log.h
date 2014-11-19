#pragma once
#include <fstream>
#include <string>

class Log {
public:
    Log(char const * path);
    virtual ~Log();
    
    // Members
    virtual void enableLog();
    virtual void disableLog();
    virtual void log(const char * msg);
    
private:
    bool _log;
    char const * _path;
    std::ofstream _file;
};