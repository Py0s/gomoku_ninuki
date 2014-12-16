#pragma once

#include "Stone.h"
#include "Map.h"
#include "APlayer.h"
#include "list"
#include <list>
#include <iostream>
#include <utility>

struct Config;

#define MAX_STONE_PLAYED    60

class Referee
{
  public:
    enum E_STATE {
        VALID = 0,
        INVALID,
        END_BLACK,
        END_WHITE,
        END_DRAW,
    };

    static const enum Stone::E_COLOR OP_COLOR[];

    Referee();
    ~Referee();
    
    // Setters
    void setConf(Config const * conf);
    
    // Members
    E_STATE check(const Stone& s, Map& map, char& captured);
    void reset();
    
    static bool gameHasEnded(const E_STATE & ret);
    
  private:
    Config const * _conf;
    std::list<std::pair<Tile&, Map::E_DIR>>    _breakables;
    
    
    /* DOUBLE THREE FUNCTIONS */
    // oui oui toutes les fonctions qui suivent c'est juste pour les double-trois ;)
    bool checkDoubleThree(Map& map, Tile& tile, Stone::E_COLOR color) const;
    bool checkDoubleThreeFirstPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    bool checkDoubleThreeSecondPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    bool checkFreeThreeConfig(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;

    bool alignOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool alignTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool alignThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;

    // bool extremOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    // bool extremTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    // bool extremThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const;
    bool XFactorextrem(Map& map, Tile& tile, Stone::E_COLOR color, int dir, int first_value, int second_value) const;

    bool alignParcours(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;

    // bool parcoursOne(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    // bool parcoursTwo(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    // bool parcoursThree(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const;
    bool XFactorParcours(Map& map, Tile& tile, Stone::E_COLOR color, int dir, int first_value, int second_value) const;

    /* CAPTURE FUNCTIONS */
    bool checkCapture(Tile& tile, Map& map, char& captured) const;

    /* ALIGNEMENT FUNCTIONS */
    Referee::E_STATE    checkAlign(Tile& t, Map& map, bool breakable);
    bool                isAlignBreakable(Tile &t, Map &m, Map::E_DIR dir);
    Map::E_OR           isTileBreakable(Tile &start, Map &m);
    bool                isOrBreakable(Tile &start, Map &m, Map::E_OR ori);
    Referee::E_STATE    checkListBreakable(Map& map);
    
    /* MEMBERS */
    Referee::E_STATE    winner(const Stone::E_COLOR color) const;
};
