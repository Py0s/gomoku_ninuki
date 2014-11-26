#include "Tile.h"

Tile::Tile()
: _color(Stone::E_COLOR::NONE) {
    for (int i=0; i < 8; ++i)
    {
        _values[Stone::BLACK][i] = 0;
        _values[Stone::WHITE][i] = 0;
        _interValues[Stone::BLACK][i] = 0;
        _interValues[Stone::WHITE][i] = 0;
    }
}

Tile::~Tile() {
}


// Getters
const char Tile::getValue(Stone::E_COLOR color, int dir) const {
    return _values[color][dir];
}

const Stone::E_COLOR&  Tile::getColor() const {
    return _color;
}


// Setters
void Tile::setValue(Stone::E_COLOR color, int dir, char value) {
    // std::cout << "(" << Y << "," << X << ")" << "[" <<  color << "]" << "[" << dir << "]" << " = " << static_cast<char>(value + '0') << std::endl;
    _values[color][dir] = value;
}

void  Tile::setColor(Stone::E_COLOR color) {
    _color = color;
}


// Debug
void Tile::Debug() const {
    std::cout << "B[" << _color << "]:";
    for (int i = 0; i < 8; ++i)
    {
        std::cout << static_cast<char>(_values[Stone::WHITE][i] + '0');
    }
    std::cout << "|N[" << _color << "]:";
    for (int i = 0; i < 8; ++i)
    {
        std::cout << static_cast<char>(_values[Stone::BLACK][i] + '0');
    }
}