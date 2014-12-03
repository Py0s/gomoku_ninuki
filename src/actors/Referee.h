#pragma once

#include "Stone.h"
#include "Map.h"
#include "APlayer.h"

struct Config;

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
    
    // Setters
    void setConf(Config const * conf);
    
    // Members
    E_STATE check(const Stone& s, Map& map, APlayer* player);
    
  private:
    Config const * _conf;
    
    /* DOUBLE THREE FUNCTIONS */
    // oui oui toutes les fonctions qui suivent c'est juste pour les double-trois ;)
    bool checkDoubleThree(Map& map, Tile& tile, Stone::E_COLOR color) const;
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

    /* CAPTURE FUNCTIONS */
    void checkCapture(Tile& tile, Map& map, APlayer* player) const;

    /* ALIGNEMENT FUNCTIONS */
    Referee::E_STATE    checkAlign(Tile& t, Map& map, bool breakable);
    bool                isAlignBreakable(const Tile &t, Map &m, Map::E_DIR dir);
    Map::E_OR           isTileBreakable(const Tile &start, Map &m) const;
    bool                isOrBreakable(const Tile &start, Map &m, Map::E_OR ori) const;
    
    /* MEMBERS */
    Referee::E_STATE    winner(const Stone::E_COLOR color) const;
};
