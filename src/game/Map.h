#pragma once

#include "Square.h"
#include <sstream>

class Map {
public:
    Map();
    virtual ~Map();
    
    // Getters
    int mapSizeX();
    int mapSizeY();
    char const * displayMap() const;
    void debugMap();

    // Setters
    void setDisplayMap(int y, int x, char c);

//    bool breakMap(int y, int x, Square::Color color);
    bool updateMap(Square::Color color);
    bool checkDoubleThree(int y, int x, Square::Color color);
    bool checkEnd(int y, int x, Square::Color color);
    bool checkBreak(int y, int x, Square::Color color);
    bool isBreakable(int y, int x, Square::Color me, Square::Color other);

    static const int _MAPSIZE_X = 19; // For now
    static const int _MAPSIZE_Y = _MAPSIZE_X;
    char _display_map[_MAPSIZE_Y][_MAPSIZE_X];
    Square _map[_MAPSIZE_Y][_MAPSIZE_X];//TODO : remettre en privee
    char _taken[2] = {0,0};

private:
    bool doubleThreeRealCheck(int y, int x, Square::Color color);
    bool doubleThreeMidLine(int y, int x, Square::Color color, Square::Direction dir);
    Square::Direction doubleThreeSquare(int y, int x, Square::Color color);
    Square::Direction doubleThreeSquareExceptDir(int y, int x, Square::Color color, Square::Direction exceptDir);
    bool doubleThreeLine(int y, int x, Square::Color color, Square::Direction dir);

    bool updateSquare(int y, int x, Square::Color color);
    bool updateSquareWithStone(int y, int x, Square::Color color);
    bool coord_ok(int y, int x);
    bool coord_not_ok(int y, int x);
    bool goToNextCase(int &y, int &x, Square::Direction dir);
    bool goToEndOfLine(int &y, int &x, Square::Color color, Square::Direction dir);
    bool updateSquareWithoutStone(int y, int x, Square::Color color);
    char lineLength(int y, int x, Square::Color color, Square::Direction dir);
    void setValue(int y, int x, Square::Color color, Square::Direction dir, char value);
    char getValue(int y, int x, Square::Color color, Square::Direction dir);
    void setInterValue(int y, int x, Square::Color color, Square::Direction dir, char value);
    char getInterValue(int y, int x, Square::Color color, Square::Direction dir);
    void updateInterValue(int y, int x, Square::Color color);

};

