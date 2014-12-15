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
    int mainLoop()
    {
        while (!(_core.quit()))
        {
            std::cout << "start of menu" << std::endl;
            menu();
            std::cout << "end of menu" << std::endl;
            start();
            std::cout << "end of game" << std::endl;
            if (gameHasEnded())
                cleanGame();
        }
        return 0;
    }

private:
    Map         _map;
    Core        _core;
    InitSfml    _init_sfml;
//    AGui*       _guis[2];
    AGui*       _gui; // Current Gui
    Menu*       _menu;
    APlayer *   _currentPlayer;
    APlayer *   _players[2];
    int         _player_nb;
    Config      _conf;
    Referee     _referee;
    Referee::E_STATE    _currentState;
    
    int menu();
    int start();
    int cleanGame();
    void initPlayers();
    inline void nextPlayer();
    void accept();
    inline bool gameHasEnded() const {
        return (_currentState == Referee::END_BLACK
            || _currentState == Referee::END_WHITE
            || _currentState == Referee::END_DRAW);
    }
};

