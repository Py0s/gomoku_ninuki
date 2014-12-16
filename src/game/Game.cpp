#include "Game.h"
#include "Sfml.h"
#include "Menu.h"
#include "AGui.h"
#include "Human.h"
#include "AI.h"
#include <iostream>

Game::Game()
: _map(), _currentPlayer(nullptr),
        _player_nb(0), _conf(), _referee() {
    _guis[static_cast<int>(MENU)] = new Menu((_init_sfml).getWindow());
    _guis[static_cast<int>(GAME)] = new Sfml(_map, _init_sfml.getWindow());
    _guiState = MENU;
}

Game::~Game() {
    delete _guis[0];
    delete _guis[1];
    if (_players[0])
        delete _players[0];
    if (_players[1])
        delete _players[1];
}

int Game::mainLoop()
{
    while (/*!(quit()) && */_conf.continue_game)
    {
        std::cout << "start of menu" << std::endl;
        menuLoop();
        switchGuiState();
        // TODO : deboguer et decommenter
        // if (!_conf.continue_game)
        //     break;
        std::cout << "end of menu" << std::endl;
        start();
        std::cout << "end of game" << std::endl;
        if (gameHasEnded())
            cleanGame();
        switchGuiState();
        std::cout << "game cleaned" << std::endl;
    }
    return 0;
}
inline void     Game::switchGuiState() {
    _guiState = (_guiState == MENU) ? (GAME) : (MENU);
    gui()->drawAll();
}


void Game::applyConf() {
    _conf = menu()->config();
    _referee.setConf(&_conf);
}

int Game::menuLoop() {
    assert(_guiState == MENU);
    menu()->drawAll();
    while (!(quit()))
    {
        menu()->refresh();
        menu()->getInput(_events);

        switch (_events.getLastKey()) {
            case EventManager::E_KEYS::UP:
                _events.disposeLastKey();
                menu()->cursorUp();
                break;
            case EventManager::E_KEYS::DOWN:
                _events.disposeLastKey();
                menu()->cursorDown();
                break;
            case EventManager::E_KEYS::LEFT:
                _events.disposeLastKey();
                menu()->cursorLeft();
                break;
            case EventManager::E_KEYS::RIGHT:
                _events.disposeLastKey();
                menu()->cursorRight();
                break;
            case EventManager::E_KEYS::ACCEPT:
                _events.disposeLastKey();
                menu()->chooseOptionValue();
                break;
            default:
                break;
        }
    }
    _events.disposeLastKey();
    applyConf();
    return 0;
}


void Game::initPlayers()
{
    assert(_guiState == GAME);
    _players[0] = (_conf.human_player_1 ?
                    dynamic_cast<APlayer *>(new Human(this->gui()->getCursor(), Stone::E_COLOR::BLACK)) :
                    dynamic_cast<APlayer *>(new AI(_map, _referee, Stone::E_COLOR::BLACK)));
    _players[1] = (_conf.human_player_2 ?
                    dynamic_cast<APlayer *>(new Human(this->gui()->getCursor(), Stone::E_COLOR::WHITE)) :
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
}

int Game::cleanGame() {
    delete this->_players[0];
    delete this->_players[1];
    this->_currentPlayer = nullptr;
    this->_players[0] = nullptr;
    this->_players[1] = nullptr;
    _map.reset();
    _referee.reset();
    _gameState = Referee::VALID;
    return 0;
}

// Members
int Game::start() {
    assert(_guiState == GAME);
    this->initPlayers();
    this->gui()->drawAll();

    while (!(this->quit()) && !(gameHasEnded()))
    {
        this->gui()->refresh();
        this->gui()->getInput(this->_events);
        if (this->_currentPlayer->getType() == APlayer::AI)
            this->_events.setKey(EventManager::E_KEYS::ACCEPT);

        switch (this->_events.getLastKey()) {
            case EventManager::E_KEYS::UP:
                this->_events.disposeLastKey();
                this->gui()->cursorUp();
                break;
            case EventManager::E_KEYS::DOWN:
                this->_events.disposeLastKey();
                this->gui()->cursorDown();
                break;
            case EventManager::E_KEYS::LEFT:
                this->_events.disposeLastKey();
                this->gui()->cursorLeft();
                break;
            case EventManager::E_KEYS::RIGHT:
                this->_events.disposeLastKey();
                this->gui()->cursorRight();
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
    _gameState = _referee.check(this->_currentPlayer->plays(), _map, this->_currentPlayer->getCaptured());
    switch (_gameState) {
        case Referee::E_STATE::VALID:
            this->nextPlayer();
            this->gui()->drawAll();
            break;
        case Referee::E_STATE::INVALID:
            break;
        case Referee::E_STATE::END_BLACK:
            this->nextPlayer();
            this->gui()->drawAll();
            menu()->setTitle("Winner Black");
            break;
        case Referee::E_STATE::END_WHITE:
            this->nextPlayer();
            this->gui()->drawAll();
            menu()->setTitle("Winner White");
            break;
        case Referee::E_STATE::END_DRAW:
            this->nextPlayer();
            this->gui()->drawAll();
            menu()->setTitle("Draw");
            break;
    }
}
