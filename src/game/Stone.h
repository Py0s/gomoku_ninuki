#pragma once

class Tile;

struct Stone {
  public:
    enum E_COLOR {
        BLACK = 0,
        WHITE,
        RED,
        NONE,
    };

    Stone(int y, int x, E_COLOR const& color = NONE);
    Stone(Tile const& tile);
    Stone(Tile const& tile, E_COLOR const& color);
    virtual ~Stone();

    // Getters
    inline E_COLOR color() const {
        return _color;
    }
    inline int y() const {
        return _y;
    }
    inline int x() const {
        return _x;
    }

    // Setters
    inline void color(E_COLOR color) {
        _color = color;
    }
    
  private:
    int _y;
    int _x;
    E_COLOR _color;
    
};
