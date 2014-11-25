#include "Map.h"

Map::Map(): OP_DIR { S, N, W, E, SW, SE, NW, NE, NONE } {
    for (int y = 0; y < this->_MAPSIZE_Y; ++y) {
        for (int x = 0; x < this->_MAPSIZE_X; ++x) {
            this->_displayMap[y][x] = Stone::E_COLOR::NONE;
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

// Members
void Map::placeStone(const Stone& s) {
    this->_displayMap[s.y()][s.x()] = s.color();
}

void Map::removeStone(const Stone& s) {
    this->_displayMap[s.y()][s.x()] = Stone::E_COLOR::NONE;
}