#pragma once
#include "Map.h"
#include "Core.h"
#include "AGui.h"
#include "Menu.h"
#include "APlayer.h"
#include "Referee.h"
#include "InitSfml.h"
#include "Config.h"
#include <map> 

class Game {
public:
    Game();
    virtual ~Game();
    
    // Members
    int mainLoop();

private:
    Map         _map;
    EventManager    _events;
//    Core        _core;
    InitSfml    _init_sfml;
//    AGui*       _guis[2];
    AGui*       _gui; // Current Gui
    Menu*       _menu;
    APlayer *   _currentPlayer;
    APlayer *   _players[2] = {NULL, NULL};
    int         _player_nb;
    Config      _conf;
    Referee     _referee;
    Referee::E_STATE    _currentState;
    
    inline bool quit() const {
        return _events.getKey(EventManager::E_KEYS::QUIT);
    }

    int menu();
    int start();
    int cleanGame();
    void initPlayers();
    inline void nextPlayer();
    void accept();
    inline bool gameHasEnded() const { return Referee::gameHasEnded(_currentState); }
};

