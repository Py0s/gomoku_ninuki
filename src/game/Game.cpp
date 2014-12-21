#include "Game.h"
#include "Goban.h"
#include "Menu.h"
#include "AGui.h"
#include "Human.h"
#include "AI.h"
#include <iostream>

Game::Game()
: _map(), _currentPlayer(nullptr),
        _player_nb(0), _conf(), _referee() {
    _guis[static_cast<int>(MENU)] = new Menu((_init_sfml).getWindow());
    _guis[static_cast<int>(GOBAN)] = new Goban(_map, _init_sfml.getWindow());
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
        if (!_conf.continue_game)
            break;
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
    _guiState = (_guiState == MENU) ? (GOBAN) : (MENU);
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
            case EventManager::UP:
                _events.disposeLastKey();
                menu()->cursorUp();
                break;
            case EventManager::DOWN:
                _events.disposeLastKey();
                menu()->cursorDown();
                break;
            case EventManager::LEFT:
                _events.disposeLastKey();
                menu()->cursorLeft();
                break;
            case EventManager::RIGHT:
                _events.disposeLastKey();
                menu()->cursorRight();
                break;
            case EventManager::ACCEPT:
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
    assert(_guiState == GOBAN);
    _players[0] = (_conf.human_player_1 ?
                    dynamic_cast<APlayer *>(new Human(gui()->getCursor(), Stone::BLACK)) :
                    dynamic_cast<APlayer *>(new AI(_map, _referee, Stone::BLACK)));
    _players[1] = (_conf.human_player_2 ?
                    dynamic_cast<APlayer *>(new Human(gui()->getCursor(), Stone::WHITE)) :
                    dynamic_cast<APlayer *>(new AI(_map, _referee, Stone::WHITE)));
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
    delete _players[0];
    delete _players[1];
    _currentPlayer = nullptr;
    _players[0] = nullptr;
    _players[1] = nullptr;
    _map.reset();
    _referee.reset();
    _gameState = Referee::VALID;
    return 0;
}

// Members
int Game::start() {
    assert(_guiState == GOBAN);
    initPlayers();
    goban()->setOptions(menu()->getOptions());
    gui()->drawAll();

    while (!(quit()) && !(gameHasEnded()))
    {
        goban()->setCaptured(_players[Stone::BLACK]->getCaptured(), _players[Stone::WHITE]->getCaptured());
        gui()->refresh();
        gui()->getInput(_events);
        if (_currentPlayer->getType() == APlayer::AI)
            _events.setKey(EventManager::ACCEPT);

        switch (_events.getLastKey()) {
            case EventManager::UP:
                _events.disposeLastKey();
                gui()->cursorUp();
                break;
            case EventManager::DOWN:
                _events.disposeLastKey();
                gui()->cursorDown();
                break;
            case EventManager::LEFT:
                _events.disposeLastKey();
                gui()->cursorLeft();
                break;
            case EventManager::RIGHT:
                _events.disposeLastKey();
                gui()->cursorRight();
                break;
            case EventManager::ACCEPT:
                _events.disposeLastKey();
                accept();
                break;
            case EventManager::BLACK:
                _events.disposeLastKey();
                if (_currentPlayer != _players[0])
                    nextPlayer();
                accept();
                break;
            case EventManager::WHITE:
                _events.disposeLastKey();
                if (_currentPlayer != _players[1])
                    nextPlayer();
                accept();
                break;
            default:
                break;
        }
    }
    _events.disposeLastKey();
    return 0;
}

inline void Game::nextPlayer() {
    _player_nb = (_player_nb + 1) % 2;
    _currentPlayer = _players[_player_nb];
}

void Game::accept() {
    _gameState = _referee.check(_currentPlayer->plays(), _map, _currentPlayer->getCaptured());
    switch (_gameState) {
        case Referee::VALID:
            nextPlayer();
            gui()->drawAll();
            break;
        case Referee::INVALID:
            break;
        case Referee::END_BLACK:
            nextPlayer();
            gui()->drawAll();
            menu()->setTitle("Winner Black");
            break;
        case Referee::END_WHITE:
            nextPlayer();
            gui()->drawAll();
            menu()->setTitle("Winner White");
            break;
        case Referee::END_DRAW:
            nextPlayer();
            gui()->drawAll();
            menu()->setTitle("Draw");
            break;
    }
}
