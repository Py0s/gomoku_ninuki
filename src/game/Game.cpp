#include "Game.h"
#include "Sfml.h"
#include "AGui.h"
#include "Human.h"
#include "AI.h"
#include <iostream>

Game::Game()
: _map(), _core(_map), _gui(new Sfml(this->_map)), _currentPlayer(NULL),
        _player_nb(0), _referee() {
    this->_conf.fivebreak_rule = true;
    this->_conf.doublethree_rule = true;
    this->_conf.ai_player_pos = -1;
    this->_referee.setConf(&this->_conf);
}

Game::~Game() {
    delete this->_gui;
}

// Members
int Game::start() {
    Human p1(this->_gui->getCursor(), Stone::E_COLOR::BLACK);
    //Human p2(this->_gui->getCursor(), Stone::E_COLOR::WHITE);
    AI p2(_map, _referee, Stone::E_COLOR::WHITE);
    p2.setTimeLimit(10);
    p2.setOpponent(&p1);

    this->_players[0] = &p1;
    this->_players[1] = &p2;
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
                this->accept();
                break;
            case EventManager::E_KEYS::BLACK:
                this->_core.eventManager().disposeLastKey();
                if (this->_currentPlayer != &p1)
                    this->nextPlayer();
                this->accept();
                break;
            case EventManager::E_KEYS::WHITE:
                this->_core.eventManager().disposeLastKey();
                if (this->_currentPlayer != &p2)
                    this->nextPlayer();
                this->accept();
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

void Game::accept() {
    Referee::E_STATE ret = _referee.check(this->_currentPlayer->plays(), _map, this->_currentPlayer->getCapturedStones());
    switch (ret) {
        case Referee::E_STATE::VALID:
            this->nextPlayer();
            this->_gui->drawMap(this->_map.displayMap());
            //if (nextPlayer is AI):
            // AI.plays()
            break;
        case Referee::E_STATE::INVALID:
            break;
        case Referee::E_STATE::END_BLACK:
            this->nextPlayer();
            this->_gui->drawMap(this->_map.displayMap());
            // this->_gui.drawWining(player_white);
            // this->_map.reset(); etc...
            std::cout << "Winner Black" << std::endl;
            break;
        case Referee::E_STATE::END_WHITE:
            this->nextPlayer();
            this->_gui->drawMap(this->_map.displayMap());
            // this->_gui.drawWining(player_white);
            // this->_map.reset(); etc...
            std::cout << "Winner White" << std::endl;
            break;
    }
}