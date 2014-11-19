#include "AGui.h"

AGui::AGui(int map_size_y, int map_size_x)
: _map_size_y(map_size_y), _map_size_x(map_size_x), _curs() {

}

AGui::~AGui() {

}

// Getters
const  Cursor& AGui::getCursor() const {
    return this->_curs;
}

// Members
bool AGui::cursorUp(const Map& m) {
    this->_curs.Y--;
    if (this->_curs.Y < 0)
        this->_curs.Y = this->_map_size_y - 1;
    return true;
}

bool AGui::cursorDown(const Map& m) {
    this->_curs.Y++;
    if (this->_curs.Y >= this->_map_size_y)
        this->_curs.Y = 0;
    return true;
}

bool AGui::cursorLeft(const Map& m) {
    this->_curs.X--;
    if (this->_curs.X < 0)
        this->_curs.X = this->_map_size_x - 1;
    return true;
}

bool AGui::cursorRight(const Map& m) {
    this->_curs.X++;
    if (this->_curs.X >= this->_map_size_x)
        this->_curs.X = 0;
    return true;
}