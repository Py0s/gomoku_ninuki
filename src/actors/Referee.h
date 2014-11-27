#pragma once

#include "Stone.h"
#include "Map.h"

class Referee
{
  public:
    enum E_STATE {
        VALID = 0,
        INVALID,
        END_BLACK,
        END_WHITE,
    };
    
    Referee();
    ~Referee();
    
    E_STATE check(const Stone& s, Map& map) const;
    void checkDoubleThree() const;
    void checkCapture(Tile& tile, Map& map) const;
    Referee::E_STATE checkAlign(Tile& t, Map& map) const;
    
  private:
    
    Referee::E_STATE winner(Stone::E_COLOR color);
};
