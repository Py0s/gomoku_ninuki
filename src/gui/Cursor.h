#pragma once

class Cursor {
  public:
    int Y;
    int X;
    
    Cursor();
    Cursor(int y, int x);
    virtual ~Cursor();
    
  private:
};

