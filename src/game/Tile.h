#pragma once
#include "Stone.h"
#include <iostream>

class Tile {
  public:
    int Y;
    int X;

    Tile();
    virtual ~Tile();

    // Getters
    const Stone::E_COLOR&  getColor() const;
    const char getValue(Stone::E_COLOR color, int dir) const;
    const char getIntValue(Stone::E_COLOR color, int dir) const;

    // Setters
    void setColor(Stone::E_COLOR color);
    void setValue(Stone::E_COLOR color, int dir, char value);

    // Debug
    void Debug() const;

  private:
    Stone::E_COLOR  _color;
    char            _values[2][8];
    char            _inter_values[2][8];
};