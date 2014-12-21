#include "Goban.h"
#include "Exceptions.h"


Goban::Goban(const Map& m, sf::RenderWindow& mainWindow)
: AGui(m.sizeY(), m.sizeX(), AGui::GOBAN), _m(m), _mainWindow(mainWindow) {
    _stone_tx.loadFromFile("./texture/stone.png");
    _stone_black_tx.loadFromFile("./texture/stone_black.png");
    _stone_white_tx.loadFromFile("./texture/stone_white.png");
    _hand_tx.loadFromFile("./texture/hand.png");
    _goban_tile_tx.loadFromFile("./texture/goban_tile.png");
    _goban_tile_tx.setRepeated(true);
    _background_tile_tx.loadFromFile("./texture/background_tile.png");
    _background_tile_tx.setRepeated(true);
    
    _background_sp.setTexture(_background_tile_tx);
    _goban_sp.setTexture(_goban_tile_tx);
    _curs_sp.setTexture(_hand_tx);
    resize();
    
    _curs.X = Map::_MAPSIZE_X / 2;
    _curs.Y = Map::_MAPSIZE_Y / 2;
    if (!_font.loadFromFile("./font/arial.ttf"))
        throw Exceptions("Can't load arial font");
    _capturedBlack = new GText("BLACK 0", &_font, GText::TITLE, 0, 0);
    _capturedWhite = new GText("WHITE 0", &_font, GText::TITLE, _mainWindow.getSize().x / 2, 0);
}

Goban::~Goban() {
}

void  Goban::setOptions(std::vector<Options*> const& options) {
    _options = options;
    drawAll();
    // int i = 1;
    // std::for_each(_options.begin(), _options.end(), [&](Options * option){
    //     option->setY(_mainWindow.getSize().y * i++ / (_options.size() + 1));
    // });
}
void  Goban::setCaptured(char black, char white) {
    std::stringstream stream2;
    std::string str2;
    stream2 << (int)black;
    stream2 >> str2;
    _capturedBlack->setString("BLACK " + str2);
    std::stringstream stream;
    std::string str;
    stream << (int)white;
    stream >> str;
    _capturedWhite->setString("WHITE " + str);
    drawAll();
}

bool Goban::getInput(EventManager& events) {
    sf::Event current;
    if (_mainWindow.isOpen() == false)
        return false;
    while (_mainWindow.pollEvent(current) == true)
    {
        switch (current.type) {
            case sf::Event::KeyPressed:
                handleKeys(current, events);
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
bool Goban::refresh() {
    drawAll();
    _mainWindow.display();    
    return true;
}

bool Goban::drawFrame(char c, const Rectangle& rect) {
    return false;
}

bool Goban::drawAll() {
    Stone::E_COLOR c;
    sf::Sprite stone;
    std::list<sf::Sprite> stones;
    const Stone::E_COLOR* map = _m.displayMap();    
    
    stone.setOrigin(_stone_white_tx.getSize().x / 2,
            _stone_white_tx.getSize().y / 2);
    stone.setScale(_SQUARE_SIZE.x / _stone_white_tx.getSize().x,
            _SQUARE_SIZE.y / _stone_white_tx.getSize().y);
    
    for (int y = 0; y < _map_size_y; ++y) {
        for (int x = 0; x < _map_size_x; ++x) {
            c = map[(y * _map_size_x) + x];
            if (c == Stone::NONE)
                continue;
            stones.push_back(stone);
            if (c == Stone::BLACK)
                stones.back().setTexture(_stone_black_tx);
            else
                stones.back().setTexture(_stone_white_tx);
            stones.back().setPosition(
                    _OFFSET_X + x * _SQUARE_SIZE.x,
                    _OFFSET_Y + y * _SQUARE_SIZE.y);
        }
    }
    _mainWindow.clear(sf::Color::Black);
    _mainWindow.draw(_background_sp);
    _mainWindow.draw(_goban_sp);
    for (std::list<sf::Sprite>::const_iterator it = stones.begin(); it != stones.end(); ++it) {
        _mainWindow.draw(*it);
    }

    _curs_sp.setPosition(
            _OFFSET_X + _curs.X * _SQUARE_SIZE.x,
            _OFFSET_Y + _curs.Y * _SQUARE_SIZE.y);
    _mainWindow.draw(_curs_sp);

    _mainWindow.draw(*_capturedWhite);
    _mainWindow.draw(*_capturedBlack);
    for (std::vector<Options *>::iterator it = _options.begin(); it < _options.end(); ++it)
        (*it)->draw();
    return true;
}

bool Goban::cursorUp() {
    _curs.Y--;
    if (_curs.Y < 0)
        _curs.Y = _map_size_y - 1;
    drawAll();
    return true;
}

bool Goban::cursorDown() {
    _curs.Y++;
    if (_curs.Y >= _map_size_y)
        _curs.Y = 0;
    drawAll();
    return true;
}

bool Goban::cursorLeft() {
    _curs.X--;
    if (_curs.X < 0)
        _curs.X = _map_size_x - 1;
    drawAll();
    return true;
}

bool Goban::cursorRight() {
    _curs.X++;
    if (_curs.X >= _map_size_x)
        _curs.X = 0;
    drawAll();
    return true;
}

bool Goban::cursorMouse(int pos_x, int pos_y) {
    return false;
}

bool Goban::newWindow(const Rectangle& rect, const std::string& msg) {
    return false;
}

/* PRIVATES */

bool Goban::handleKeys(const sf::Event& current, EventManager& events) {
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

void Goban::resize() {
    sf::Vector2f target_size = _mainWindow.getView().getSize();

    _background_sp.setTextureRect(sf::IntRect(0, 0, target_size.x, target_size.y));

    sf::Vector2u size = _goban_tile_tx.getSize();
    _goban_sp.setTextureRect(sf::IntRect(0, 0, size.x * (Map::_MAPSIZE_X - 1), size.y * (Map::_MAPSIZE_Y - 1)));

    _goban_sp.setScale(target_size.x / _goban_sp.getLocalBounds().width * 0.90,
            target_size.y / _goban_sp.getLocalBounds().height * 0.90);
    _goban_sp.setPosition(
            target_size.x / 2 - _goban_sp.getGlobalBounds().width / 2,
            target_size.y / 2 - _goban_sp.getGlobalBounds().height / 2 - 25);
    
    _curs_sp.setScale(0.75 * target_size.x / _goban_sp.getLocalBounds().width
            ,0.75 * target_size.y / _goban_sp.getLocalBounds().height);
    
    _OFFSET_X = _goban_sp.getGlobalBounds().left;
    _OFFSET_Y = _goban_sp.getGlobalBounds().top;
    _SQUARE_SIZE = sf::Vector2f(
            _goban_tile_tx.getSize().x * _goban_sp.getScale().x,
            _goban_tile_tx.getSize().y * _goban_sp.getScale().y);
}