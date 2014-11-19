#include "Debug.h"

Debug::Debug(): Log("./debug.log") {

}

Debug::Debug(char const * path): Log(path) {

}

Debug::~Debug() {

}