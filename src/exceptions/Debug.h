#pragma once
#include "Log.h"

class Debug: public Log {
public:

    Debug();
    Debug(char const * path);
    virtual ~Debug();
    
private:
};