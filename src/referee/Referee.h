#pragma once

#include "stone.h"

class Referee
{
public:
    Referee();
    ~Referee();

    bool check();
    
private:
    std::list<int>  _winningSquares;
    std::list<int>  _futurTakenSquares;
    std::list<int>  _doubleThreeSquares;
};
