#pragma once
#include "Map.h"
#include "Core.h"
#include "AGui.h"
#include "IPlayer.h"
#include <map> 

class Game {
public:
    Game();
    virtual ~Game();
    
    // Members
    int start();
    
private:
    Map _map;
    Core _core;
    AGui* _gui;
    IPlayer * _playing;
};

