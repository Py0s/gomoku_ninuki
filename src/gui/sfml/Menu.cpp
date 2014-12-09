#include "Menu.h"

Menu::Menu(sf::RenderWindow& mainWindow)
: AGui(0, 0, AGui::GAME), _mainWindow(mainWindow) {

}

Menu::~Menu() {
}

bool Menu::getInput(EventManager& events) {
    sf::Event current;
    if (this->_mainWindow.isOpen() == false)
        return false;
    while (this->_mainWindow.pollEvent(current) == true)
    {
        switch (current.type) {
            case sf::Event::KeyPressed:
                this->handleKeys(current, events);
                break;
            case sf::Event::Closed:
                events.setKey(EventManager::E_KEYS::QUIT);
                break;
            default:
                break;
        }
    }
    return true;
}

// Members
bool Menu::refresh() {
    this->_mainWindow.display();
    return true;
}

bool Menu::drawFrame(char c, const Rectangle& rect) { // Not used
    return false;
}

bool Menu::drawMap(const Stone::E_COLOR* map) { // This is general drawing func
    return false;
}

bool Menu::cursorUp(const Map& m) {
    AGui::cursorUp(m);
    this->drawMap(m.displayMap());
    return true;
}

bool Menu::cursorDown(const Map& m) {
    AGui::cursorDown(m);
    this->drawMap(m.displayMap());
    return true;
}

bool Menu::cursorLeft(const Map& m) {
    AGui::cursorLeft(m);
    this->drawMap(m.displayMap());
    return true;
}

bool Menu::cursorRight(const Map& m) {
    AGui::cursorRight(m);
    this->drawMap(m.displayMap());
    return true;
}

bool Menu::cursorMouse(int pos_x, int pos_y) {
    return false;
}

bool Menu::newWindow(const Rectangle& rect, const std::string& msg) {
    return false;
}

/* PRIVATES */

bool Menu::handleKeys(const sf::Event& current, EventManager& events) {
    switch (current.key.code) {
        case (sf::Keyboard::Up):
            events.setKey(EventManager::E_KEYS::UP);
            break;
        case (sf::Keyboard::Down):
            events.setKey(EventManager::E_KEYS::DOWN);
            break;
        case (sf::Keyboard::Left):
            events.setKey(EventManager::E_KEYS::LEFT);
            break;
        case (sf::Keyboard::Right):
            events.setKey(EventManager::E_KEYS::RIGHT);
            break;
        case (sf::Keyboard::Return):
            events.setKey(EventManager::E_KEYS::ACCEPT);
            break;
        case (sf::Keyboard::Escape):
            events.setKey(EventManager::E_KEYS::QUIT);
            break;
        case (sf::Keyboard::Z):
        case (sf::Keyboard::W):
            events.setKey(EventManager::E_KEYS::BLACK);
            break;
        case (sf::Keyboard::X):
            events.setKey(EventManager::E_KEYS::WHITE);
            break;
        default:
            break;
    }
    return true;
}