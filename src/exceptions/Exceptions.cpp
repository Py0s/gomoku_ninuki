#include "Exceptions.h"

Exceptions::Exceptions(std::string what) : _what(what) {
    
}

Exceptions::~Exceptions() {
    
}

// Getters
const char* Exceptions::what() const throw() {
    return this->_what.c_str();
}

const int Exceptions::errNo() const throw () {
    return 1;
}