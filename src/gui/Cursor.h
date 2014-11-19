#pragma once

class Cursor {
  public:
    Cursor();
    Cursor(int y, int x);
    virtual ~Cursor();

    // Getters
    int y() const;
    int x() const;
    
  private:    
    int Y;
    int X;
};

