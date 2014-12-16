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
    enum E_GUI_STATE {
        MENU = 0,
        GAME,
    };

    Game();
    virtual ~Game();
    
    // Members
    int mainLoop();

private:
    Map         _map;
    EventManager    _events;
    InitSfml    _init_sfml;
    AGui*       _guis[2];
    E_GUI_STATE _guiState;

    APlayer *   _currentPlayer;
    APlayer *   _players[2] = {NULL, NULL};
    int         _player_nb;
    Config      _conf;
    Referee     _referee;
    Referee::E_STATE    _gameState;
    
    inline bool quit() const {
        return _events.getKey(EventManager::E_KEYS::QUIT);
    }

    inline AGui*    gui() { return _guis[static_cast<int>(_guiState)]; }
    inline Menu*    menu() {
        assert(_guiState == MENU);
        return dynamic_cast<Menu*>(gui());
    }
    inline void     switchGuiState() {
        _guiState = (_guiState == MENU) ? (GAME) : (MENU);
    }

    int menuLoop();
    int start();
    int cleanGame();
    void initPlayers();
    inline void nextPlayer();
    void accept();
    inline bool gameHasEnded() const { return Referee::gameHasEnded(_gameState); }
};

