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

const Stone::E_COLOR&  Tile::getColor() const {
    return _color;
}

void  Tile::color(Stone::E_COLOR color) {
    _color = color;
}