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
//        NONE,
        MAX, // Should NEVER be used
    };
    
    static const enum E_DIR OP_DIR[];

    typedef Tile& (Map::*PTR) (Tile&);
    const PTR go[MAX] = { &Map::nw, &Map::n, &Map::ne, &Map::e,   \
                          &Map::se, &Map::s, &Map::sw, &Map::w, NULL };
    
    Map();
    virtual ~Map();
    
    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;
    std::array<std::array<Tile, 19>, 19>& getMap();
        
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(const Stone& s);
  
    // Debug
    void displayDebug() const;
    
  private:
    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;

    Stone::E_COLOR   _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
    std::array<std::array<Tile, 19>, 19>    _map;

    void updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile);
    
    Tile& n(Tile& t);
    Tile& s(Tile& t);
    Tile& e(Tile& t);
    Tile& w(Tile& t);
    
    Tile& ne(Tile& t);
    Tile& nw(Tile& t);
    Tile& se(Tile& t);
    Tile& sw(Tile& t);
};