#pragma once

#include "APlayer.h"
#include "Cursor.h"
#include "Map.h"
#include "Referee.h"

#define AI_INFINITY    100000

class AI : public APlayer
{
    public:
        AI(Map& map, Referee& referee, Stone::E_COLOR color);
        virtual ~AI();

        virtual Stone    plays();

        // Setters
        void setOpponent(APlayer * player);
        void setTimeLimit(float t);// limite en secondes

    private:
        Map&        _map;
        Referee&    _referee;
        APlayer *   _opponent;
        Stone::E_COLOR _opColor;
        float       _timeLimit;
        float       _playBeginTime;

        inline void        checkTime();

        //Fonction qui calcule le prochain coup
        Stone calc(int depth);
 
        //Fonctions pour le calcul
        int calcMinMax(Map& map, int depth, Referee::E_STATE ret, Stone::E_COLOR color, int alpha, int beta);
        int calcMin(Map& map, int depth, Referee::E_STATE ret,/* char& captured, char& opponentCaptured,*/ int alpha, int beta);
        int calcMax(Map& map, int depth, Referee::E_STATE ret,/* char& captured, char& opponentCaptured,*/ int alpha, int beta);
 
        //Fonction qui évalue le jeu
        int eval(Map& map, Referee::E_STATE ret);
        int eval(Map& map, Referee::E_STATE ret, char captured, char opponentCaptured);
};
