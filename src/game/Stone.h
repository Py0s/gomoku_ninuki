#pragma once

class Stone {
  public:
    enum E_COLOR {
        BLACK = 0,
        WHITE,
        NONE,
    };

    Stone(int y, int x);
    Stone(int y, int x, E_COLOR color);
    virtual ~Stone();

    // Getters
    E_COLOR color() const;
    int y() const;
    int x() const;
    
    // Setters
    void color(E_COLOR color);
    
  private:
    int _y;
    int _x;
    E_COLOR _color;
    
};
