#include "InitSfml.h"

InitSfml::InitSfml() {
    _mainWindow.create(sf::VideoMode(1920, 1080, 32), "Gomoku");
    _mainWindow.setVerticalSyncEnabled(true);
}

InitSfml::~InitSfml() {
    _mainWindow.close();
}

sf::RenderWindow& InitSfml::getWindow() {
    return _mainWindow;
}