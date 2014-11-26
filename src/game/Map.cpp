#include "Map.h"
#include "ExcOutOfBound.h"

const enum Map::E_DIR Map::OP_DIR[] = { SE, S, SW, W, NW, N, NE, E };

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
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
void Map::placeStone(const Stone& s) {
    Tile& tile = _map[s.y()][s.x()];
    Stone::E_COLOR color = s.color();

    this->_displayMap[s.y()][s.x()] = color;
    tile.setColor(color);

    for (int dir=0; dir < 8; ++dir)
    {
        try
        {
            Tile& next_tile = CALL_MEMBER_FN(*this, go[dir])(tile);
            updateTile(color, dir, tile.getValue(color, (dir + 4) % 8) + 1, next_tile); // Change modulo by opposite direction
        }
        catch (const ExcOutOfBound& e) {
        }
    }
}

void Map::removeStone(const Stone& s) {
    Tile& tile = _map[s.y()][s.x()];
    Stone::E_COLOR color = Stone::E_COLOR::NONE;

    this->_displayMap[s.y()][s.x()] = color;
    tile.setColor(color);

    for (int dir=0; dir < 8; ++dir)
    {
        try
        {
            Tile& next_tile = CALL_MEMBER_FN(*this, go[dir])(tile);
            updateTile(color, dir, 0, next_tile);
        }
        catch (const ExcOutOfBound& e) {
        }
    }
}

void Map::updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile) {
    // std::cout << "Update Tile (" << color << ") dir:" << dir << std::endl;
    tile.setValue(color, (dir + 4) % 8, value); // Change modulo by opposite direction
    if (tile.getColor() != Stone::E_COLOR::NONE)
    {
        try
        {
            Tile& next_tile = CALL_MEMBER_FN(*this, go[dir])(tile);
            updateTile(color, dir, ++value, next_tile);
        }
        catch (const ExcOutOfBound& e) {
        }
    }
}


// Debug
void Map::displayDebug() const
{
    for (int y=0; y < 5; ++y)
    {
        for (int x = 0; x < 2; ++x)
        {
            _map[y][x].Debug();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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