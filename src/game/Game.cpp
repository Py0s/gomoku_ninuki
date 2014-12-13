#include "Game.h"
#include "Sfml.h"
#include "Menu.h"
#include "AGui.h"
#include "Human.h"
#include "AI.h"
#include <iostream>

Game::Game()
: _map(), _core(_map), _currentPlayer(NULL),
        _player_nb(0), _referee() {
    this->_conf.human_player_1 = false;
    this->_conf.human_player_2 = false;
    this->_conf.fivebreak_rule = true;
    this->_conf.doublethree_rule = true;
    this->_conf.ai_time = 0.1;
    this->_referee.setConf(&this->_conf);

    this->_guis[0] = new Menu((this->_init_sfml).getWindow());
    this->_guis[1] = new Sfml(this->_map, this->_init_sfml.getWindow());
    this->_gui = this->_guis[0];
}

Game::~Game() {
    delete this->_guis[0];
    delete this->_guis[1];
    delete this->_players[0];
    delete this->_players[1];
}

void Game::initPlayers()
{
    _players[0] = (_conf.human_player_1 ?
                    dynamic_cast<APlayer *>(new Human(this->_gui->getCursor(), Stone::E_COLOR::BLACK)) :
                    dynamic_cast<APlayer *>(new AI(_map, _referee, Stone::E_COLOR::BLACK)));
    _players[1] = (_conf.human_player_2 ?
                    dynamic_cast<APlayer *>(new Human(this->_gui->getCursor(), Stone::E_COLOR::WHITE)) :
                    dynamic_cast<APlayer *>(new AI(_map, _referee, Stone::E_COLOR::WHITE)));
    if (_players[0]->getType() == APlayer::AI)
    {
        dynamic_cast<AI *>(_players[0])->setTimeLimit(_conf.ai_time);
        dynamic_cast<AI *>(_players[0])->setOpponent(_players[1]);
    }
    if (_players[1]->getType() == APlayer::AI)
    {
        dynamic_cast<AI *>(_players[1])->setTimeLimit(_conf.ai_time);
        dynamic_cast<AI *>(_players[1])->setOpponent(_players[0]);
    }
    _currentPlayer = _players[0];

    // Human * p1 = new Human(this->_gui->getCursor(), Stone::E_COLOR::BLACK);
    // if (this->_conf.ai_player_pos == -1)
    // {
    //     Human * p2 = new Human(this->_gui->getCursor(), Stone::E_COLOR::WHITE);
    //     this->_players[0] = p1;
    //     this->_players[1] = p2;
    // }
    // else
    // {
    //     AI * p2 = new AI(_map, _referee, Stone::E_COLOR::WHITE);
    //     p2->setTimeLimit(1.5);
    //     p2->setOpponent(p1);
    //     this->_players[this->_conf.ai_player_pos] = p2;
    //     this->_players[(this->_conf.ai_player_pos + 1) % 2] = p1;
    // }
    // this->_currentPlayer = this->_players[0];
}

int Game::restart() {
    delete this->_players[0];
    delete this->_players[1];
    // TODO : clean tout ce qu'il faut entre 2 parties
    // clean map, referee, conf ?
    return start();
}

// Members
int Game::start() {
    this->initPlayers();
    this->_gui->drawAll();

    while (this->_core.quit() == false)
    {
        this->_gui->refresh();
        this->_gui->getInput(this->_core.eventManager());
        if (this->_currentPlayer->getType() == APlayer::AI)
            this->_core.eventManager().setKey(EventManager::E_KEYS::ACCEPT);

        switch (this->_core.eventManager().getLastKey()) {
            case EventManager::E_KEYS::UP:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorUp();
                break;
            case EventManager::E_KEYS::DOWN:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorDown();
                break;
            case EventManager::E_KEYS::LEFT:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorLeft();
                break;
            case EventManager::E_KEYS::RIGHT:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorRight();
                break;
            case EventManager::E_KEYS::ACCEPT:
                this->_core.eventManager().disposeLastKey();
                this->accept();
                break;
            case EventManager::E_KEYS::BLACK:
                this->_core.eventManager().disposeLastKey();
                if (this->_currentPlayer != this->_players[0])
                    this->nextPlayer();
                this->accept();
                break;
            case EventManager::E_KEYS::WHITE:
                this->_core.eventManager().disposeLastKey();
                if (this->_currentPlayer != this->_players[1])
                    this->nextPlayer();
                this->accept();
                break;
            default:
                break;
        }
    }
    return 0;
}
int Game::menu() {
    this->_gui->drawAll();

    while (this->_core.quit() == false)
    {
        this->_gui->refresh();
        this->_gui->getInput(this->_core.eventManager());

        switch (this->_core.eventManager().getLastKey()) {
            case EventManager::E_KEYS::UP:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorUp();
                break;
            case EventManager::E_KEYS::DOWN:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorDown();
                break;
            case EventManager::E_KEYS::LEFT:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorLeft();
                break;
            case EventManager::E_KEYS::RIGHT:
                this->_core.eventManager().disposeLastKey();
                this->_gui->cursorRight();
                break;
            case EventManager::E_KEYS::ACCEPT:
                this->_core.eventManager().disposeLastKey();
                (dynamic_cast<Menu *>(this->_gui))->chooseOptionValue();
                break;
            default:
                break;
        }
    }
    this->_core.eventManager().disposeLastKey();
    this->_conf = (dynamic_cast<Menu *>(this->_gui))->config();
    this->_gui = this->_guis[1];
    return 0;
}

inline void Game::nextPlayer() {
    this->_player_nb = (this->_player_nb + 1) % 2;
    this->_currentPlayer = this->_players[this->_player_nb];
}

void Game::accept() {
    Referee::E_STATE ret = _referee.check(this->_currentPlayer->plays(), _map, this->_currentPlayer->getCaptured());
    switch (ret) {
        case Referee::E_STATE::VALID:
            this->nextPlayer();
            this->_gui->drawAll();
            break;
        case Referee::E_STATE::INVALID:
            break;
        case Referee::E_STATE::END_BLACK:
            this->nextPlayer();
            this->_gui->drawAll();
            std::cout << "Winner Black" << std::endl;
            // this->_gui.drawWining(player_white);
            // this->_map.reset(); etc...
            break;
        case Referee::E_STATE::END_WHITE:
            this->nextPlayer();
            this->_gui->drawAll();
            std::cout << "Winner White" << std::endl;
            // this->_gui.drawWining(player_white);
            // this->_map.reset(); etc...
            break;
    }
}
