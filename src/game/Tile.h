#pragma once
#include "Stone.h"
#include <iostream>

class Tile {
  public:
    int     Y;
    int     X;
    bool    _breakable;

    Tile();
    virtual ~Tile();

    void reset();

    // Getters
    inline bool isEmpty() const { return (_color == Stone::E_COLOR::NONE); }
    inline const Stone::E_COLOR  getColor() const { return _color; }
    inline const char  getValue(Stone::E_COLOR color, int dir) const { return _values[color][dir]; }
    inline const char  getIntValue(Stone::E_COLOR color, int dir) const { return _inter_values[color][dir % 4]; }// TODO : Virer ce fuding modulo 4

    // Setters
    inline void setColor(Stone::E_COLOR color) { _color = color; }
    inline void setValue(Stone::E_COLOR color, int dir, char value) { _values[color][dir] = value; }
    inline void AddToInterValue(Stone::E_COLOR color, int dir, char value) { _inter_values[color][dir] += value; }

    // Debug
    void Debug() const;

private:
    Stone::E_COLOR  _color;
    char            _values[2][8];
    char            _inter_values[2][8];
};
