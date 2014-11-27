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


// Operators
std::array<Tile, 19>& Map::operator[](size_t idx) {
    return _map[idx];
}


// Members
//#define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))
void Map::placeStone(const Stone& s) {
    Tile& tile = _map[s.y()][s.x()];
    Stone::E_COLOR color = s.color();

    this->_displayMap[s.y()][s.x()] = color;
    tile.setColor(color);

    for (int dir=0; dir < 8; ++dir)
    {
        try
        {
            //Tile& next_tile = (*this.go[dir])(tile);
            //Tile& next_tile = CALL_MEMBER_FN(this, go[dir])(tile);
            PTR ptr = this->go[dir];
            Tile& next_tile = (this->*ptr)(tile, 1);
            updateTile(color, dir, tile.getValue(color, (dir + 4) % 8) + 1, next_tile); // TODO: Change modulo by opposite direction
        }
        catch (const ExcOutOfBound& e) {
        }
    }
}

void Map::removeStone(Tile& tile) {
    Stone::E_COLOR color = tile.getColor();

    this->_displayMap[tile.Y][tile.X] = Stone::E_COLOR::NONE;
    tile.setColor(Stone::E_COLOR::NONE);

    for (int dir=0; dir < 8; ++dir)
    {
        try
        {
            PTR ptr = this->go[dir];
            Tile& next_tile = (this->*ptr)(tile, 1);
            //Tile& next_tile = CALL_MEMBER_FN(*this, go[dir])(tile);
            updateTile(color, dir, 0, next_tile);
        }
        catch (const ExcOutOfBound& e) {
        }
    }
}

void Map::updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile) {
    // std::cout << "Update Tile (" << color << ") dir:" << dir << std::endl;
    tile.setValue(color, (dir + 4) % 8, value); // TODO: Change modulo by opposite direction
    if (tile.getColor() == color)
    {
        try
        {
            PTR ptr = this->go[dir];
            Tile& next_tile = (this->*ptr)(tile, 1);
            //Tile& next_tile = CALL_MEMBER_FN(*this, go[dir])(tile);
            updateTile(color, dir, ++value, next_tile);
        }
        catch (const ExcOutOfBound& e) {
        }
    }
}


// Debug
void Map::displayDebug() const
{
    for (int y=0; y < 2; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            _map[y][x].Debug();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// PRIVATE
Tile& Map::n(Tile& t, unsigned char len) {
    char y = t.Y - 1 * len;
    char x = t.X;

    if (y < 0)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::s(Tile& t, unsigned char len) {
    char y = t.Y + 1 * len;
    char x = t.X;

    if (y >= this->_MAPSIZE_Y)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::e(Tile& t, unsigned char len) {
    char y = t.Y;
    char x = t.X + 1 * len;

    if (x>= this->_MAPSIZE_X)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::w(Tile& t, unsigned char len) {
    char y = t.Y;
    char x = t.X - 1 * len;

    if (x < 0)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::ne(Tile& t, unsigned char len) {
    char y = t.Y - 1 * len;
    char x = t.X + 1 * len;

    if (y < 0 || x >= this->_MAPSIZE_X)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::nw(Tile& t, unsigned char len) {
    char y = t.Y - 1 * len;
    char x = t.X - 1 * len;

    if (y < 0 || x < 0)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::se(Tile& t, unsigned char len) {
    char y = t.Y + 1 * len;
    char x = t.X + 1 * len;

    if (y >= this->_MAPSIZE_Y || x >= this->_MAPSIZE_X)
        throw ExcOutOfBound();
    return this->_map[y][x];
}

Tile& Map::sw(Tile& t, unsigned char len) {
    char y = t.Y + 1 * len;
    char x = t.X - 1 * len;

    if (y >= this->_MAPSIZE_Y || x < 0)
        throw ExcOutOfBound();
    return this->_map[y][x];
}