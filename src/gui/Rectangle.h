#pragma once

class Rectangle {
public:
    Rectangle(int pos_y, int pos_x, int size_y, int size_x);
    virtual ~Rectangle();

    // Getters
    int x() const;
    int y() const;
    int sizeX() const;
    int sizeY() const;
    
    // Setters
    void x(int pos_x);
    void y(int pos_y);
    void sizeX(int size_x);
    void sizeY(int size_y);
    
private:
    int _pos_y;
    int _pos_x;
    int _size_y;
    int _size_x;
    
};

