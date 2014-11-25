#pragma once
#include "Stone.h"

class Tile {
  public:
    Tile();
    virtual ~Tile();

    const Stone::E_COLOR&  getColor() const;
    void color(Stone::E_COLOR color);

  private:
    Stone::E_COLOR  _color;
    char            _values[2][8];
    char            _interValues[2][8];
};