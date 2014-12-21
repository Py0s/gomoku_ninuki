#include "Rectangle.h"

Rectangle::Rectangle(int pos_y, int pos_x, int size_y, int size_x)
: _pos_y(pos_y), _pos_x(pos_x), _size_y(size_y), _size_x(size_x)
{ }

Rectangle::~Rectangle() {
}

// Getters
int Rectangle::x() const {
    return _pos_x;
}

int Rectangle::y() const {
    return _pos_y;
}

int Rectangle::sizeX() const {
    return _size_x;
}

int Rectangle::sizeY() const {
    return _size_y;
}

// Setters

void Rectangle::x(int pos_x) {
    _pos_x = pos_x;
}

void Rectangle::y(int pos_y) {
    _pos_y = pos_y;
}

void Rectangle::sizeX(int size_x) {
    _size_x = size_x;
}

void Rectangle::sizeY(int size_y) {
    _size_y = size_y;
}