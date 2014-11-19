#include "Stone.h"

Stone::Stone(int y, int x): _y(y), _x(x) {
}

Stone::Stone(int y, int x, Stone::E_COLOR color): _y(y), _x(x), _color(color) {
}

Stone::~Stone() {
}

// Getters
Stone::E_COLOR Stone::color() const {
    return this->_color;
}

int Stone::y() const {
    return this->_y;
}

int Stone::x() const {
    return this->_x;
}

// Setters
void Stone::color(Stone::E_COLOR color) {
    this->_color = color;
}
