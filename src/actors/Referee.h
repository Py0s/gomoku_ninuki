#pragma once

#include "Stone.h"
#include "Map.h"
#include "APlayer.h"
#include "list"
#include <list>
#include <iostream>
#include <utility>

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
    
    E_STATE check(const Stone& s, Map& map, APlayer* player);
    void    checkDoubleThree() const;
    void    checkCapture(Tile& tile, Map& map, APlayer* player) const;
    Referee::E_STATE    checkAlign(Tile& t, Map& map);
    void    checkLbreakables(Map& map);


private:

    std::list<std::pair<Tile, Map::E_DIR>>    _breakables;
    bool                    isAlignBreakable(const Tile &t, Map &m, Map::E_DIR dir);
    bool                    isBreakable(const Tile &start, Map &m);
    Referee::E_STATE        winner(const Stone::E_COLOR color) const;
};
