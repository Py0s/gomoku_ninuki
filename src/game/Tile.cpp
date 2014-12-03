#include "Tile.h"

Tile::Tile()
: _color(Stone::E_COLOR::NONE) {
    for (int i=0; i < 8; ++i)
    {
        _values[Stone::BLACK][i] = 0;
        _values[Stone::WHITE][i] = 0;
        _inter_values[Stone::BLACK][i] = 0;
        _inter_values[Stone::WHITE][i] = 0;
    }
}

Tile::~Tile() {
}


// Getters
const char Tile::getValue(Stone::E_COLOR color, int dir) const {
    return _values[color][dir];
}

const char Tile::getIntValue(Stone::E_COLOR color, int dir) const {
    return this->_inter_values[color][dir % 4]; // TODO : Virer ce fuding modulo 4
}

const Stone::E_COLOR  Tile::getColor() const {
    return _color;
}


// Setters
void  Tile::setColor(Stone::E_COLOR color) {
    _color = color;
}

void Tile::setValue(Stone::E_COLOR color, int dir, char value) {
    _values[color][dir] = value;
}

void Tile::AddToInterValue(Stone::E_COLOR color, int dir, char value) {
    _inter_values[color][dir] += value;
}




// Debug
void Tile::Debug() const {
    std::cout << "B:";
    /*for (int i = 0; i < 8; ++i)
    {
        std::cout << static_cast<char>(_values[Stone::WHITE][i] + '0');
    }
    std::cout << "|N:";
    for (int i = 0; i < 8; ++i)
    {
        std::cout << static_cast<char>(_values[Stone::BLACK][i] + '0');
    }*/
    for (int i = 0; i < 4; ++i)
    {
        std::cout << static_cast<char>(_inter_values[Stone::WHITE][i] + '0');
    }
    std::cout << "|N:";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << static_cast<char>(_inter_values[Stone::BLACK][i] + '0');
    }
}