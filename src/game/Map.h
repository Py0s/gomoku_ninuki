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
    static const enum E_DIR FROM_DIR[4] = {N, W, NE, NW};
    
    typedef Tile& (Map::*PTR) (Tile&, unsigned char);
    const PTR go[MAX] = { &Map::nw, &Map::n, &Map::ne, &Map::e,   \
                          &Map::se, &Map::s, &Map::sw, &Map::w, NULL };
    
    Map();
    virtual ~Map();
    
    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;


    // Operator
    std::array<Tile, 19>& operator[](size_t idx);
        
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(Tile& tile);
  
    // Debug
    void displayDebug() const;
    
  private:
    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;

    Stone::E_COLOR   _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
    std::array<std::array<Tile, 19>, 19>    _map;

    void updateTile(Stone::E_COLOR color, int dir, char value, Tile& tile, char inter_value);
    
    Tile& n(Tile& t, unsigned char len);
    Tile& s(Tile& t, unsigned char len);
    Tile& e(Tile& t, unsigned char len);
    Tile& w(Tile& t, unsigned char len);
    
    Tile& ne(Tile& t, unsigned char len);
    Tile& nw(Tile& t, unsigned char len);
    Tile& se(Tile& t, unsigned char len);
    Tile& sw(Tile& t, unsigned char len);
};