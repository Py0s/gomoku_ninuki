#pragma once
#include "Stone.h"
#include "Cursor.h"
#include "Tile.h"
#include <array>


class Map {
  public:
    enum E_DIR {
        NW = 0,
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        DIR_COUNT,// = number of elements in the enum
    };
    
    enum E_OR {
        NS = 0,
        NESW,
        EW,
        SENW,
        MAX,
    };
    
    static const enum E_DIR OP_DIR[];
    static const enum E_DIR OR_TO_DIR[];

    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;
        
    typedef Tile& (Map::*PTR) (const Tile&, unsigned char);
    const PTR go[DIR_COUNT] = { &Map::nw, &Map::n, &Map::ne, &Map::e,   \
                          &Map::se, &Map::s, &Map::sw, &Map::w };
    
    Map();
    virtual ~Map();

    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;
    char getPlayed() {return _played;}

    // Operator
    std::array<Tile, _MAPSIZE_X>& operator[](size_t idx);
        
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(Tile& tile);
    void played() {_played++;}
  
    // Debug
    void displayDebug() const;
    
  private:
    char _played;

    Stone::E_COLOR   _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
    std::array<std::array<Tile, _MAPSIZE_X>, _MAPSIZE_Y>    _map;

    void updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile, char inter_value);
    
    Tile& n(const Tile& t, unsigned char len);
    Tile& s(const Tile& t, unsigned char len);
    Tile& e(const Tile& t, unsigned char len);
    Tile& w(const Tile& t, unsigned char len);
    
    Tile& ne(const Tile& t, unsigned char len);
    Tile& nw(const Tile& t, unsigned char len);
    Tile& se(const Tile& t, unsigned char len);
    Tile& sw(const Tile& t, unsigned char len);
};