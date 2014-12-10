#include "InitSfml.h"

InitSfml::InitSfml() {
    this->_mainWindow.create(sf::VideoMode(1920, 1080, 32), "Gomoku");
    this->_mainWindow.setVerticalSyncEnabled(true);
}

InitSfml::~InitSfml() {
    this->_mainWindow.close();
}

sf::RenderWindow& InitSfml::getWindow() {
    return this->_mainWindow;
}