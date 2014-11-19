#include "Log.h"
#include "Exceptions.h"
#include <iostream>

Log::Log(char const * path): _log(true), _path(path) {
    this->_file.open(this->_path, std::ios::out | std::ios::trunc);
    if (this->_file.is_open() == false) {
        throw Exceptions("Could not open file");
    }
}

Log::~Log() {
    if (this->_file.is_open() == true) {
        this->_file.close();
    }
}

// Members

void Log::enableLog() {
    this->_log = true;
}

void Log::disableLog() {
    this->_log = false;
}

void Log::log(const char * msg) {
    if (this->_log == true)
        this->_file << msg << '\n';
}