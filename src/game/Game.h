#pragma once
#include "Map.h"
#include "Core.h"
#include "AGui.h"
#include "Square.h"
#include <map> 

class Game {
public:
    Game(bool ncurses);
    virtual ~Game();
    
    // Members
    int start();
    
private:
    Map _map;
    Core _core;
    Square::Color _player;
    std::map<Square::Color, char> _visual;
    AGui* _gui;
};

