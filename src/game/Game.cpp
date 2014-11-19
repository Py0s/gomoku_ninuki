#include "Game.h"
#include "Sfml.h"
#include "AGui.h"
#include <iostream>

Game::Game()
: _map(), _core(_map) {
    this->_gui = new Sfml(this->_map);
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
                this->_map.placeStone(Stone(this->_gui->getCursor().Y, this->_gui->getCursor().X, Stone::E_COLOR::WHITE));
                this->_gui->drawMap(this->_map.displayMap());
                break;
            default:
                break;
        }
    }
    return 0;
}
