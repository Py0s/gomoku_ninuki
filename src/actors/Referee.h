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
    
    E_STATE check(const Stone& s, Map& map, APlayer* player);
    bool checkDoubleThree(Map& map, Tile& tile, Stone::E_COLOR color) const;
    void checkCapture(Tile& tile, Map& map, APlayer* player) const;
    Referee::E_STATE checkAlign(Tile& t, Map& map);
    
  private:
    
    // oui oui toutes les fonctions qui suivent c'est juste pour les double-trois ;)
    bool checkDoubleThreeFirstPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    bool checkDoubleThreeSecondPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    bool checkFreeThreeConfig(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool alignOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool extremOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool alignTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool extremTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool alignThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool extremThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;

    bool XFactorextrem(Map& map, Tile& tile, Stone::E_COLOR color, int dir, int first_value, int second_value) const;

    /* ALIGNEMENT FUNCTIONS */
    bool                isAlignBreakable(const Tile &t, Map &m, Map::E_DIR dir);
    Map::E_OR           isTileBreakable(const Tile &start, Map &m) const;
    bool                isOrBreakable(const Tile &start, Map &m, Map::E_OR ori) const;
    
    Referee::E_STATE    winner(const Stone::E_COLOR color) const;
};
