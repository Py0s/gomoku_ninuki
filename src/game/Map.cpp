#include "Map.h"
#include "ExcOutOfBound.h"
#include "Referee.h"

const enum Map::E_DIR Map::OP_DIR[] = { SE, S, SW, W, NW, N, NE, E };
const enum Map::E_DIR Map::OR_TO_DIR[] = {N, NE, E, SE};

Map::Map() : _stonesPlayed(0) {
    for (int y = 0; y < _MAPSIZE_Y; ++y) {
        for (int x = 0; x < _MAPSIZE_X; ++x) {
            _displayMap[y][x] = Stone::NONE;
            _map[y][x].Y = y;
            _map[y][x].X = x;
        }
    }
}

Map::~Map() {
}

// Getters
int Map::sizeX() const {
    return _MAPSIZE_X;
}

int Map::sizeY() const {
    return _MAPSIZE_Y;
}

const Stone::E_COLOR * Map::displayMap() const {
    return (Stone::E_COLOR*)(_displayMap);
}


// Operators
std::array<Tile, Map::_MAPSIZE_X>& Map::operator[](size_t idx) {
    return _map[idx];
}


// Members
void Map::placeStone(const Stone& s) {
    Tile& tile = getTile(s);
    Stone::E_COLOR color = s.color();

    _displayMap[s.y()][s.x()] = color;
    _played[color]++;
    tile.setColor(color);

    for (int dir_inter = 0; dir_inter < 4; ++dir_inter)
    {
        tile.AddToInterValue(color, dir_inter, 1);
    }

    for (int dir=0; dir < 8; ++dir)
    {
        bool outOfBound = false;
//        try
//        {
            PTR ptr = go[dir];
            Tile& next_tile = (this->*ptr)(outOfBound, tile, 1);
            if (!outOfBound) {
                char value = tile.getValue(color, Map::OP_DIR[dir]) + 1;
                updateTile(color, dir, value, next_tile, value);
            }
//        }
//        catch (const ExcOutOfBound& e) {
//        }
    }
}

void Map::removeStone(Tile& tile) {
    Stone::E_COLOR color = tile.getColor();

    _displayMap[tile.Y][tile.X] = Stone::NONE;
    _played[color]--;
    tile.setColor(Stone::NONE);

    for (int dir_inter = 0; dir_inter < 4; ++dir_inter)
    {
        tile.AddToInterValue(color, dir_inter, -1);
    }

    for (int dir=0; dir < 8; ++dir)
    {
        bool outOfBound = false;
//        try
//        {
            PTR ptr = go[dir];
            Tile& next_tile = (this->*ptr)(outOfBound, tile, 1);
            if (!outOfBound) {
                updateTile(color, dir, 0, next_tile, -(tile.getValue(color, Map::OP_DIR[dir]) + 1));
            }
//        }
//        catch (const ExcOutOfBound& e) {
//        }
    }
}

void Map::updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile, char inter_value) {
    tile.setValue(color, Map::OP_DIR[dir], value);
    tile.AddToInterValue(color, dir, inter_value);
    if (tile.getColor() == color)
    {
        bool outOfBound = false;
//        try
//        {
            PTR ptr = go[dir];
            Tile& next_tile = (this->*ptr)(outOfBound, tile, 1);
            if (!outOfBound) {
                updateTile(color, dir, ++value, next_tile, inter_value);
            }
//        }
//        catch (const ExcOutOfBound& e) {
//        }
    }
}

void Map::reset() {
    _stonesPlayed = 0;
    _played[Stone::WHITE] = 0;
    _played[Stone::BLACK] = 0;
    _captured[Stone::WHITE] = 0;
    _captured[Stone::BLACK] = 0;
    for (int y = 0; y < _MAPSIZE_Y; ++y)
    {
        for (int x = 0; x < _MAPSIZE_X; ++x)
        {
            getTile(y, x).reset();
            _displayMap[y][x] = Stone::NONE;
        }
    }
}


// Debug
void Map::displayDebug() const
{
    for (int y=0; y < 5; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            std::cout << _map[y][x].getColor() << "|";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// PRIVATE
Tile& Map::n(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y - 1 * len;
    char x = t.X;

    if (y < 0) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::s(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y + 1 * len;
    char x = t.X;

    if (y >= _MAPSIZE_Y) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::e(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y;
    char x = t.X + 1 * len;

    if (x >= _MAPSIZE_X) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::w(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y;
    char x = t.X - 1 * len;

    if (x < 0) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::ne(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y - 1 * len;
    char x = t.X + 1 * len;

    if (y < 0 || x >= _MAPSIZE_X) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::nw(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y - 1 * len;
    char x = t.X - 1 * len;

    if (y < 0 || x < 0) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::se(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y + 1 * len;
    char x = t.X + 1 * len;

    if (y >= _MAPSIZE_Y || x >= _MAPSIZE_X) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}

Tile& Map::sw(bool& outOfBound, const Tile& t, unsigned char len) {
    char y = t.Y + 1 * len;
    char x = t.X - 1 * len;

    if (y >= _MAPSIZE_Y || x < 0) {
        outOfBound = true;
        return _map[0][0];
        // throw ExcOutOfBound();
    }
    return _map[y][x];
}