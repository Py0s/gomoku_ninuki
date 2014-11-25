#pragma once
#include "Stone.h"
#include "Cursor.h"
#include "Tile.h"

class Map {
  public:
    enum E_DIR {
        N = 0,
        S,
        E,
        W,
        NE,
        SE,
        NW,
        SW,
        NONE,
        MAX,
    };
    
    const enum E_DIR OP_DIR[MAX];
    
    Map();
    virtual ~Map();
    
    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;
    
    Tile& n(Tile);
    Tile& s(Tile);
    Tile& e(Tile);
    Tile& w(Tile);
    
    Tile& ne(Tile);
    Tile& nw(Tile);
    Tile& se(Tile);
    Tile& sw(Tile);
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(const Stone& s);
  
    
  private:
    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;
    
    Stone::E_COLOR _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
};