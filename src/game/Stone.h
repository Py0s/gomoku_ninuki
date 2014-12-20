#pragma once

class Tile;

struct Stone {
  public:
    enum E_COLOR {
        BLACK = 0,
        WHITE,
        NONE,
    };

    Stone(int y, int x, E_COLOR const& color = NONE);
    Stone(Tile const& tile);
    Stone(Tile const& tile, E_COLOR const& color);
    virtual ~Stone();

    // Getters
    inline E_COLOR color() const {
        return this->_color;
    }
    inline int y() const {
        return this->_y;
    }
    inline int x() const {
        return this->_x;
    }

    // Setters
    inline void color(E_COLOR color) {
        this->_color = color;
    }
    
  private:
    int _y;
    int _x;
    E_COLOR _color;
    
};
