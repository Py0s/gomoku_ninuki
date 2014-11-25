#include "Map.h"
#include "ExcOutOfBound.h"

const enum Map::E_DIR Map::OP_DIR[] = { S, N, W, E, SW, SE, NW, NE, NONE };

Map::Map() {
    for (int y = 0; y < this->_MAPSIZE_Y; ++y) {
        for (int x = 0; x < this->_MAPSIZE_X; ++x) {
            this->_displayMap[y][x] = Stone::E_COLOR::NONE;
            _map[y][x].Y = y;
            _map[y][x].X = x;
        }
    }
}

Map::~Map() {
}

// Getters
int Map::sizeX() const {
    return this->_MAPSIZE_X;
}

int Map::sizeY() const {
    return this->_MAPSIZE_Y;
}

const Stone::E_COLOR * Map::displayMap() const {
    return (Stone::E_COLOR*)(this->_displayMap);
}

std::array<std::array<Tile, 19>, 19>& Map::getMap() {
    return (_map);
}


// Members
void Map::placeStone(const Stone& s) {
    this->_displayMap[s.y()][s.x()] = s.color();
    this->_map[s.y()][s.x()].color(s.color());
}

void Map::removeStone(const Stone& s) {
    this->_displayMap[s.y()][s.x()] = Stone::E_COLOR::NONE;
}

// PRIVATE
Tile& Map::n(Tile& t) {
    if (t.Y - 1 < 0)
        throw ExcOutOfBound();
    return this->_map[t.Y - 1][t.X];
}

Tile& Map::s(Tile& t) {
    if (t.Y + 1 >= this->_MAPSIZE_Y)
        throw ExcOutOfBound();
    return this->_map[t.Y + 1][t.X];
}

Tile& Map::e(Tile& t) {
    if (t.X + 1 >= this->_MAPSIZE_X)
        throw ExcOutOfBound();
    return this->_map[t.Y][t.X + 1];
}

Tile& Map::w(Tile& t) {
    if (t.X - 1 < 0)
        throw ExcOutOfBound();
    return this->_map[t.Y][t.X - 1];
}

Tile& Map::ne(Tile& t) {
    if (t.Y - 1 < 0 || t.X + 1 >= this->_MAPSIZE_X)
        throw ExcOutOfBound();
    return this->_map[t.Y - 1][t.X + 1];
}

Tile& Map::nw(Tile& t) {
    if (t.Y - 1 < 0 || t.X - 1 < 0)
        throw ExcOutOfBound();
    return this->_map[t.Y - 1][t.X - 1];
}

Tile& Map::se(Tile& t) {
    if (t.Y + 1 >= this->_MAPSIZE_Y || t.X + 1 >= this->_MAPSIZE_X)
        throw ExcOutOfBound();
    return this->_map[t.Y + 1][t.X + 1];
}

Tile& Map::sw(Tile& t) {
    if (t.Y + 1 >= this->_MAPSIZE_Y || t.X - 1 < 0)
        throw ExcOutOfBound();
    return this->_map[t.Y + 1][t.X - 1];
}