#include "EventManager.h"

EventManager::EventManager(): _lastKey(E_KEYS::NONE) {
    for (int i = E_KEYS::NONE; i < E_KEYS::MAX; ++i)
        _keys[i] = false;
}

EventManager::~EventManager() {
    
}

// Setters
void EventManager::setKey(E_KEYS key, bool activate) {
    _keys[key] = activate;
    if (activate == true)
        _lastKey = key;
}

// Getters
bool EventManager::getKey(E_KEYS key) const {
    return _keys[key];
}

bool EventManager::getDisposeKey(E_KEYS key) {
  bool state = EventManager::getKey(key);
  disposeKey(key);
  return state;
}

EventManager::E_KEYS EventManager::getLastKey() {
    return _lastKey;
}

EventManager::E_KEYS EventManager::getDisposeLastKey() {
    E_KEYS key = EventManager::getLastKey();
    _lastKey = E_KEYS::NONE;
    disposeKey(key);
    return key;
}

void EventManager::disposeKey(E_KEYS key) {
    _keys[key] = false;
}

void EventManager::disposeLastKey() {
    disposeKey(_lastKey);
    _lastKey = E_KEYS::NONE;
}
