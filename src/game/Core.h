#pragma once
#include "EventManager.h"
#include "Map.h"

class Core {
public:
  Core(Map& map);
  ~Core();
  
  // Getters
  EventManager& eventManager();

  // Members
  bool quit() const;

private:
    EventManager _events;
    Map _map;
    
};