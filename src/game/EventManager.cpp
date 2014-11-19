#include "EventManager.h"

EventManager::EventManager(): _lastKey(E_KEYS::NONE) {
    for (int i = E_KEYS::NONE; i < E_KEYS::MAX; ++i)
        this->_keys[i] = false;
}

EventManager::~EventManager() {
    
}

// Setters
void EventManager::setKey(E_KEYS key, bool activate) {
    this->_keys[key] = activate;
    if (activate == true)
        this->_lastKey = key;
}

// Getters
bool EventManager::getKey(E_KEYS key) const {
    return this->_keys[key];
}

bool EventManager::getDisposeKey(E_KEYS key) {
  bool state = EventManager::getKey(key);
  this->disposeKey(key);
  return state;
}

EventManager::E_KEYS EventManager::getLastKey() {
    return this->_lastKey;
}

EventManager::E_KEYS EventManager::getDisposeLastKey() {
    E_KEYS key = EventManager::getLastKey();
    this->_lastKey = E_KEYS::NONE;
    this->disposeKey(key);
    return key;
}

void EventManager::disposeKey(E_KEYS key) {
    this->_keys[key] = false;
}

void EventManager::disposeLastKey() {
    this->disposeKey(this->_lastKey);
    this->_lastKey = E_KEYS::NONE;
}