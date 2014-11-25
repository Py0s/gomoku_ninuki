#include "Map.h"

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
    Tile tile = _map[s.y()][s.x()];
    Stone::E_COLOR color = s.color();

    this->_displayMap[s.y()][s.x()] = color;
    tile.setColor(color);

    for (int dir=0; dir < 8; ++dir)
        updateTile(color, dir, tile.getValue(color, dir + 4 % 8), tile); // A CHANGER AVEC FONCTION DIRECTION OPPOSEE
}

void Map::removeStone(const Stone& s) {
    Tile tile = _map[s.y()][s.x()];
    Stone::E_COLOR color = Stone::E_COLOR::NONE;

    this->_displayMap[s.y()][s.x()] = color;
    tile.setColor(color);

    for (int dir=0; dir < 8; ++dir)
        updateTile(color, dir, 0, tile); // A CHANGER AVEC FONCTION DIRECTION OPPOSEE    
}


void Map::updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile) {
    tile.setValue(color, dir + 4 % 8, value);
    if (tile.getColor() != Stone::E_COLOR::NONE)
    {
            Tile next_tile = tile;
            updateTile(color, dir, ++value, next_tile);
    }
}