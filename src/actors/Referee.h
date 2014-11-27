#pragma once

#include "Stone.h"
#include "Map.h"
#include "APlayer.h"

class Referee
{
  public:
    enum E_STATE {
        VALID = 0,
        INVALID,
        END_BLACK,
        END_WHITE,
    };

    static const enum Stone::E_COLOR OP_COLOR[];
    
    Referee();
    ~Referee();
    
    E_STATE check(const Stone& s, Map& map, APlayer* player) const;
    void checkDoubleThree() const;
    void checkCapture(Tile& tile, Map& map, APlayer* player) const;
    Referee::E_STATE checkAlign(Tile& t, Map& map) const;
    
  private:
    
    Referee::E_STATE winner(const Stone::E_COLOR color) const;
};
