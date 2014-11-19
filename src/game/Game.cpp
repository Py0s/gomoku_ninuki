#include "Game.h"
#include "NCurses.h"
#include "Sfml.h"
#include "AGui.h"
#include <iostream>

Game::Game(bool ncurses)
: _map(), _core(_map), _player(Square::BLACK) {
    this->_visual[Square::BLACK] = 'X';
    this->_visual[Square::WHITE] = 'O';
    // Set default displayMap for NCurses. Should be changed or moved
    for (int y = 0; y < this->_map.mapSizeY(); ++y)
      for (int x = 0; x < this->_map.mapSizeX(); ++x)
        this->_map.setDisplayMap(y, x, '*');
    if (ncurses == true) // TODO: make gui givable
        this->_gui = new NCurses(this->_map.mapSizeY(), this->_map.mapSizeX());
    else
        this->_gui = new Sfml(this->_map.mapSizeY(), this->_map.mapSizeX());
}

Game::~Game() {
    delete this->_gui;
}

// Members
int Game::start() {
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
                //this->_gui->newWindow(Rectangle(0, 0, 3, 10), "Winner");
                // TODO: Should be changed with map setter going through Referee etc...


                if (_map._map[this->_gui->getCursor().Y][this->_gui->getCursor().X]._player != Square::UNDEFINED)
                    break;
                if (this->_map.checkDoubleThree(this->_gui->getCursor().Y, this->_gui->getCursor().X, this->_player))
                {
                    std::cout << "Double-Three ! You can not play on this intersection!" << std::endl;
                }
                else
                {
                    _map._map[this->_gui->getCursor().Y][this->_gui->getCursor().X]._player = _player;
                    if (this->_map.updateMap(/*this->_gui->getCursor().Y, this->_gui->getCursor().X, */this->_player))
                    {
                        //Si la ou je joue il y as un 3 dans autre equipe check sandwich

                        this->_map.checkBreak(this->_gui->getCursor().Y, this->_gui->getCursor().X, this->_player);
                        ///////////VICTORY//////////// Return true si victoire
                        this->_map.checkEnd(this->_gui->getCursor().Y, this->_gui->getCursor().X, this->_player);
                        /////////////////////////////

                        // TODO : update seulement les cases prises
                        for (int y = 0; y < this->_map.mapSizeY(); ++y)
                          for (int x = 0; x < this->_map.mapSizeX(); ++x)
                          {
                            if (_map._map[y][x]._player != Square::UNDEFINED)
                                this->_map.setDisplayMap(y, x, this->_visual[_map._map[y][x]._player]);
                            else
                                this->_map.setDisplayMap(y, x, '*');
                            }

                        this->_map.setDisplayMap(this->_gui->getCursor().Y, this->_gui->getCursor().X, this->_visual[this->_player]);
                        if (this->_player == Square::BLACK)
                            this->_player = Square::WHITE;
                        else
                            this->_player = Square::BLACK;
                    }
                    this->_gui->drawMap(this->_map.displayMap());
                    this->_map.debugMap();
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
