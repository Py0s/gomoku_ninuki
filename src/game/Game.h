#pragma once
#include "Map.h"
#include "Core.h"
#include "AGui.h"
#include "Menu.h"
#include "Goban.h"
#include "APlayer.h"
#include "Referee.h"
#include "InitSfml.h"
#include "Config.h"
#include <map> 

class Game {
public:
    enum E_GUI_STATE {
        MENU = 0,
        GOBAN,
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
    APlayer *   _players[2] = {nullptr, nullptr};
    int         _player_nb;
    Config      _conf;
    Referee     _referee;
    Referee::E_STATE    _gameState;
    
    inline AGui*    gui() { return _guis[static_cast<int>(_guiState)]; }
    inline Menu*    menu() { return dynamic_cast<Menu*>(_guis[static_cast<int>(MENU)]); }
    inline Goban*   goban() { return dynamic_cast<Goban*>(_guis[static_cast<int>(GOBAN)]); }
    inline void     switchGuiState();

    inline bool quit() const { return _events.getKey(EventManager::E_KEYS::QUIT); }
    void applyConf();
    int menuLoop();
    int start();
    int cleanGame();

    void initPlayers();
    inline void nextPlayer();
    void accept();
    inline bool gameHasEnded() const { return Referee::gameHasEnded(_gameState); }
};

