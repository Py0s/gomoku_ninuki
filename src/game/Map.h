#pragma once
#include "Stone.h"
#include "Cursor.h"

class Map {
public:
    Map();
    virtual ~Map();
    
    // Getters
    int sizeX() const;
    int sizeY() const;
    const Stone::E_COLOR * displayMap() const;
    
    // Members
    void placeStone(const Stone& s);
    void removeStone(const Stone& s);
    
private:
    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;

    Stone::E_COLOR _displayMap[_MAPSIZE_Y][_MAPSIZE_X];
};

