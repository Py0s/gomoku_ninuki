#pragma once

class Cursor {
public:
    Cursor();
    Cursor(int y, int x);
    virtual ~Cursor();
    
    int Y;
    int X;
};

