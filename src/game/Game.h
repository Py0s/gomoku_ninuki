#pragma once
#include "Map.h"
#include "Core.h"
#include "AGui.h"
#include "IPlayer.h"
#include "Referee.h"
#include <map> 

struct Config {
    bool doublethree_rule;
    bool fivebreak_rule;
    int ai_player_pos; // Set -1 if no ai
};

class Game {
public:
    Game();
    virtual ~Game();
    
    // Members
    int start();
    
private:
    Map         _map;
    Core        _core;
    AGui*       _gui;
    IPlayer *   _currentPlayer;
    IPlayer *   _players[2];
    int         _player_nb;
    Config      _conf;
    Referee     _referee;
    
    inline void nextPlayer();
};

