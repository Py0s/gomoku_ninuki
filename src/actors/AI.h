#pragma once

#include "APlayer.h"
#include "Cursor.h"
#include "Map.h"
#include "Referee.h"
#include <vector>
#include <utility>

#define AI_INFINITY    100000
// typedef Tile     TILE_VALUE_T;
typedef std::pair<int,int>          TILE_VALUE_T;//FOR NOW
typedef std::vector<TILE_VALUE_T>   TILE_VEC_T;
typedef TILE_VEC_T::iterator        TILE_IT_T;
typedef TILE_VEC_T::const_iterator  CONST_TILE_IT_T;

class AI : public APlayer
{
    public:
        AI(Map& map, Referee& referee, Stone::E_COLOR color);
        virtual ~AI();

        virtual Stone    plays();

        // Setters
        void setOpponent(APlayer * player);
        void setTimeLimit(float durationSeconds);

    private:
        Map&        _map;
        Referee&    _referee;
        APlayer *   _opponent;
        Stone::E_COLOR _opColor;
        float       _durationSeconds;
        float       _playBeginTime;
        TILE_VEC_T  _openTiles;
        TILE_VEC_T  _closeTiles;

        void        checkTime();

        //Fonction qui calcule le prochain coup
        Stone calc(int depth);
 
        //Fonctions pour le calcul
        int calcMinMax(Map& map, int depth, Referee::E_STATE ret, Stone::E_COLOR color, int alpha, int beta);
        int getEvalForFirstMovePossible(Map& map, int depth, Stone::E_COLOR color, int alpha, int beta, int &y, int &x);
        int calcMin(Map& map, int depth, Referee::E_STATE ret, int alpha, int beta);
        int calcMax(Map& map, int depth, Referee::E_STATE ret, int alpha, int beta);
 
        //Fonction qui évalue le jeu
        int eval(Map& map, Referee::E_STATE ret, Stone::E_COLOR color);
        // int eval(Map& map, Referee::E_STATE ret);

        //A* functions
        void initOpenTiles();
        // void initOpenTilesDebug(Map& map);
        void closeTile(TILE_IT_T & it);

};
