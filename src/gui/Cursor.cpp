#include "Cursor.h"

Cursor::Cursor() : Y(0), X(0) {
}

Cursor::Cursor(int y, int x) : Y(y), X(x) {
}

Cursor::~Cursor() {
}

// Getters

int Cursor::y() const {
    return this->Y;
}

int Cursor::x() const {
    return this->X;
}