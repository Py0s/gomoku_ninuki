#pragma once
#include "Stone.h"
#include "Cursor.h"
#include "Tile.h"
#include <array>

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
    
    static const enum E_DIR OP_DIR[];
    
    Map();
    virtual ~Map();
    
    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;
    std::array<std::array<Tile, 19>, 19>& getMap();
    
    Tile& n(Tile t);
    Tile& s(Tile t);
    Tile& e(Tile t);
    Tile& w(Tile t);
    
    Tile& ne(Tile t);
    Tile& nw(Tile t);
    Tile& se(Tile t);
    Tile& sw(Tile t);
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(const Stone& s);
  
    
  private:
    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;

    Stone::E_COLOR                          _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
    std::array<std::array<Tile, 19>, 19>    _map;
};