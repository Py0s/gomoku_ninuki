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

    static const int _MAPSIZE_X = 9;
    static const int _MAPSIZE_Y = _MAPSIZE_X;

    // static const int _MAPSIZE_X = 9; // For now
    // static const int _MAPSIZE_Y = 5;
    
    typedef Tile& (Map::*PTR) (const Tile&, unsigned char);
    const PTR go[DIR_COUNT] = { &Map::nw, &Map::n, &Map::ne, &Map::e,   \
                          &Map::se, &Map::s, &Map::sw, &Map::w };
    
    Map();
    virtual ~Map();

    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;
    char getPlayed() {return _stonesPlayed;}
    char getPlayed(Stone::E_COLOR color) {return _played[color];}
    char getCapturedBy(Stone::E_COLOR color) {return _captured[color];}

    // Operator
    std::array<Tile, _MAPSIZE_X>& operator[](size_t idx);
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(Tile& tile);
    void played() {_stonesPlayed++;}
    void addCaptured(Stone::E_COLOR color, char value) { _captured[color] += value;}
    void reset();
  
    // Debug
    void displayDebug() const;
    
  private:
    char _stonesPlayed;
    char _played[2] = {0,0};
    char _captured[2] = {0,0};

    Stone::E_COLOR   _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
    std::array<std::array<Tile, _MAPSIZE_X>, _MAPSIZE_Y>    _map;

    inline Tile& getTile(int y, int x) { return _map[y][x]; }
    inline Tile& getTile(Stone const& s) { return _map[s.y()][s.x()]; }
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
