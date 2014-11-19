#include "Core.h"

Core::Core(Map& map)
: _events(), _map(map) {

}

Core::~Core() {
    
}

// Getters
EventManager& Core::eventManager() {
    return this->_events;
}

// Members
bool Core::quit() const {
    return this->_events.getKey(EventManager::E_KEYS::QUIT);
}
