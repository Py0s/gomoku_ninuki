#include "Game.h"
#include "Sfml.h"
#include "Menu.h"
#include "AGui.h"
#include "Human.h"
#include "AI.h"
#include <iostream>

Game::Game()
: _map(), _currentPlayer(NULL),
        _player_nb(0), _conf(), _referee() {
    _referee.setConf(&_conf);
    // _guis[0] = new Menu((_init_sfml).getWindow());
    // _guis[1] = new Sfml(_map, _init_sfml.getWindow());
    _menu = new Menu((_init_sfml).getWindow());
    _gui = new Sfml(_map, _init_sfml.getWindow());
}

Game::~Game() {
    delete _menu;
    delete _gui;
//    if (_players[0])
//        delete _players[0];
//    if (_players[1])
//        delete _players[1];
}

int Game::mainLoop()
{
    while (!(quit()) && _conf.continue_game)
    {
        std::cout << "start of menu" << std::endl;
        menu();
        // TODO : deboguer et decommenter
        // if (!_conf.continue_game)
        //     break;
        std::cout << "end of menu" << std::endl;
        start();
        std::cout << "end of game" << std::endl;
        if (gameHasEnded())
            cleanGame();
    }
    return 0;
}

int Game::menu() {
    _menu->drawAll();
    while (!(quit()))
    {
        _menu->refresh();
        _menu->getInput(_events);

        switch (_events.getLastKey()) {
            case EventManager::E_KEYS::UP:
                _events.disposeLastKey();
                _menu->cursorUp();
                break;
            case EventManager::E_KEYS::DOWN:
                _events.disposeLastKey();
                _menu->cursorDown();
                break;
            case EventManager::E_KEYS::LEFT:
                _events.disposeLastKey();
                _menu->cursorLeft();
                break;
            case EventManager::E_KEYS::RIGHT:
                _events.disposeLastKey();
                _menu->cursorRight();
                break;
            case EventManager::E_KEYS::ACCEPT:
                _events.disposeLastKey();
                _menu->chooseOptionValue();
                break;
            default:
                break;
        }
    }
    _events.disposeLastKey();
    _conf = _menu->config();
    return 0;
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

int Game::cleanGame() {
    delete this->_players[0];
    delete this->_players[1];
    // TODO : clean tout ce qu'il faut entre 2 parties
    // clean map, referee, conf ?

//    _map.reset();
    _currentState = Referee::VALID;
    return 0;
}

// Members
int Game::start() {
    this->initPlayers();
    this->_gui->drawAll();

    while (!(this->quit()) && !(gameHasEnded()))
    {
        this->_gui->refresh();
        this->_gui->getInput(this->_events);
        if (this->_currentPlayer->getType() == APlayer::AI)
            this->_events.setKey(EventManager::E_KEYS::ACCEPT);

        switch (this->_events.getLastKey()) {
            case EventManager::E_KEYS::UP:
                this->_events.disposeLastKey();
                this->_gui->cursorUp();
                break;
            case EventManager::E_KEYS::DOWN:
                this->_events.disposeLastKey();
                this->_gui->cursorDown();
                break;
            case EventManager::E_KEYS::LEFT:
                this->_events.disposeLastKey();
                this->_gui->cursorLeft();
                break;
            case EventManager::E_KEYS::RIGHT:
                this->_events.disposeLastKey();
                this->_gui->cursorRight();
                break;
            case EventManager::E_KEYS::ACCEPT:
                this->_events.disposeLastKey();
                this->accept();
                break;
            case EventManager::E_KEYS::BLACK:
                this->_events.disposeLastKey();
                if (this->_currentPlayer != this->_players[0])
                    this->nextPlayer();
                this->accept();
                break;
            case EventManager::E_KEYS::WHITE:
                this->_events.disposeLastKey();
                if (this->_currentPlayer != this->_players[1])
                    this->nextPlayer();
                this->accept();
                break;
            default:
                break;
        }
    }
    _events.disposeLastKey();
    return 0;
}

inline void Game::nextPlayer() {
    this->_player_nb = (this->_player_nb + 1) % 2;
    this->_currentPlayer = this->_players[this->_player_nb];
}

void Game::accept() {
    _currentState = _referee.check(this->_currentPlayer->plays(), _map, this->_currentPlayer->getCaptured());
    switch (_currentState) {
        case Referee::E_STATE::VALID:
            this->nextPlayer();
            this->_gui->drawAll();
            break;
        case Referee::E_STATE::INVALID:
            break;
        case Referee::E_STATE::END_BLACK:
            this->nextPlayer();
            this->_gui->drawAll();
            _menu->setTitle("Winner Black");
            break;
        case Referee::E_STATE::END_WHITE:
            this->nextPlayer();
            this->_gui->drawAll();
            _menu->setTitle("Winner White");
            break;
        case Referee::E_STATE::END_DRAW:
            this->nextPlayer();
            this->_gui->drawAll();
            _menu->setTitle("Draw");
            break;
    }
}
