#include "Game.h"
#include "Sfml.h"
#include "AGui.h"
#include "Human.h"
#include <iostream>

Game::Game()
: _map(), _core(_map), _gui(new Sfml(this->_map)), _currentPlayer(NULL), _player_nb(0) {
    this->_players[0] = new Human(this->_gui->getCursor(), Stone::E_COLOR::BLACK);
    this->_players[1] = new Human(this->_gui->getCursor(), Stone::E_COLOR::WHITE);
}

Game::~Game() {
    delete this->_players[0];
    delete this->_players[1];
    delete this->_gui;
}

// Members
int Game::start() {

    this->_currentPlayer = this->_players[0];
    this->_gui->drawMap(this->_map.displayMap());
    while (this->_core.quit() == false)
    {
        this->_gui->refresh();
        this->_gui->getInput(this->_core.eventManager());

        switch (this->_core.eventManager().getLastKey()) {
            case EventManager::E_KEYS::UP:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorUp(this->_map);
                break;
            case EventManager::E_KEYS::DOWN:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorDown(this->_map);
                break;
            case EventManager::E_KEYS::LEFT:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorLeft(this->_map);
                break;
            case EventManager::E_KEYS::RIGHT:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorRight(this->_map);
                break;
            case EventManager::E_KEYS::ACCEPT:
                this->_core.eventManager().disposeLastKey();

                // This is the call to all rules. player.Plays() will return the stone which need to be placed.
                // Should return True if it's valid
                // bool valid = Referee.check(this->currentPlayer.plays())
                //if (nextPlayer is AI): AI.plays())
                // Continue

                this->_map.placeStone(this->_currentPlayer->plays());
                this->_gui->drawMap(this->_map.displayMap());
                this->nextPlayer();
                break;
            default:
                break;
        }
    }
    return 0;
}

inline void Game::nextPlayer() {
    this->_player_nb = (this->_player_nb + 1) % 2;
    this->_currentPlayer = this->_players[this->_player_nb];
}