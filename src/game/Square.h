#pragma once

#include <utility>
#include "SquareInfo.h"

class Square
{
public:
    enum Color      { WHITE = 0, BLACK, UNDEFINED};
    enum Direction  { UP_LEFT=0, LEFT_UP=0,
                      UP=1, 
                      UP_RIGHT=2, RIGHT_UP=2,
                      RIGHT=3,
                      DOWN_RIGHT=4, RIGHT_DOWN=4,
                      DOWN=5,
                      DOWN_LEFT=6, LEFT_DOWN=6,
                      LEFT=7, 
                      DIRECTION_COUNT=8 };
    Square();
    ~Square();

    static Direction opposedDirection(Direction const& dir)
    {
      return static_cast<Direction>((static_cast<int>(dir) + 4) % 8);
    }

    // return (x,y) to add to the actual position to have the next one
    static std::pair<int,int> directionToVector(Direction const& dir);
    // return (x,y) the position of the next case in the direction
    // static std::pair<int,int> const& nextPosInDirection(Direction const& dir, std::pair<int,int>& pos);
    static Direction vectorToDirection(std::pair<int,int> const& coord);

    static Color opponentColor(Color color);
public:
    Color           _player;
    SquareInfo      _infos[2];
};