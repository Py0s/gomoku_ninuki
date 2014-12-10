#include "Sfml.h"

Sfml::Sfml(const Map& m, sf::RenderWindow& mainWindow)
: AGui(m.sizeY(), m.sizeX(), AGui::GAME), _m(m), _mainWindow(mainWindow) {
    this->_mainWindow.clear(sf::Color::Black);

    this->_goban_tile_tx.loadFromFile("./texture/goban_tile.png");
    this->_goban_tile_tx.setRepeated(true);

    this->_stone_tx.loadFromFile("./texture/stone.png");

    this->_hand_tx.loadFromFile("./texture/hand.png");

    this->_goban_sp.setTexture(this->_goban_tile_tx);
    this->_goban_sp.setTextureRect(sf::IntRect(0, 0, 50 * (this->_map_size_x + 1), 50 * (this->_map_size_y + 1)));
    
    this->_curs_sp.setTexture(this->_hand_tx);
    this->_curs_sp.setScale(0.3, 0.3);

}

Sfml::~Sfml() {
}

bool Sfml::getInput(EventManager& events) {
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
bool Sfml::refresh() {
    this->_mainWindow.display();
    return true;
}

bool Sfml::drawFrame(char c, const Rectangle& rect) {
    return false;
}

bool Sfml::drawAll() {
    Stone::E_COLOR c;
    std::list<sf::Sprite> stones;
    const Stone::E_COLOR* map = this->_m.displayMap();
    
    this->_mainWindow.clear(sf::Color::Black);
    for (int y = 0; y < this->_map_size_y; ++y) {
        for (int x = 0; x < this->_map_size_x; ++x) {
            c = map[(y * this->_map_size_x) + x];
            if (c == Stone::E_COLOR::NONE)
                continue;
            stones.push_back(sf::Sprite());
            stones.back().setTexture(this->_stone_tx);
            if (c == Stone::E_COLOR::BLACK)
                stones.back().setColor(sf::Color(75, 75, 75));
            stones.back().setPosition(Sfml::OFFSET_X + (x * 50), Sfml::OFFSET_Y + (y * 50));
        }
    }
    this->_mainWindow.draw(this->_goban_sp);
    for (std::list<sf::Sprite>::const_iterator it = stones.begin(); it != stones.end(); ++it) {
        this->_mainWindow.draw(*it);
    }

    this->_curs_sp.setPosition(OFFSET_X + this->_curs.X * 50, OFFSET_Y + this->_curs.Y * 50);
    this->_mainWindow.draw(this->_curs_sp);

    return true;
}

bool Sfml::cursorUp() {
    this->_curs.Y--;
    if (this->_curs.Y < 0)
        this->_curs.Y = this->_map_size_y - 1;
    this->drawAll();
    return true;
}

bool Sfml::cursorDown() {
    this->_curs.Y++;
    if (this->_curs.Y >= this->_map_size_y)
        this->_curs.Y = 0;
    this->drawAll();
    return true;
}

bool Sfml::cursorLeft() {
    this->_curs.X--;
    if (this->_curs.X < 0)
        this->_curs.X = this->_map_size_x - 1;
    this->drawAll();
    return true;
}

bool Sfml::cursorRight() {
    this->_curs.X++;
    if (this->_curs.X >= this->_map_size_x)
        this->_curs.X = 0;
    this->drawAll();
    return true;
}

bool Sfml::cursorMouse(int pos_x, int pos_y) {
    return false;
}

bool Sfml::newWindow(const Rectangle& rect, const std::string& msg) {
    return false;
}

/* PRIVATES */

bool Sfml::handleKeys(const sf::Event& current, EventManager& events) {
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