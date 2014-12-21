#include "Log.h"
#include "Exceptions.h"
#include <iostream>

Log::Log(char const * path): _log(true), _path(path) {
    _file.open(_path, std::ios::out | std::ios::trunc);
    if (_file.is_open() == false) {
        throw Exceptions("Could not open file");
    }
}

Log::~Log() {
    if (_file.is_open() == true) {
        _file.close();
    }
}

// Members

void Log::enableLog() {
    _log = true;
}

void Log::disableLog() {
    _log = false;
}

void Log::log(const char * msg) {
    if (_log == true)
        _file << msg << '\n';
}