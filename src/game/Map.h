#pragma once

class Map {
public:
    Map();
    virtual ~Map();
    
    // Getters
    int sizeX() const;
    int sizeY() const;

private:
    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;

};

