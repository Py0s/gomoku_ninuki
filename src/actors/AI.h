#pragma once

#include "APlayer.h"
#include "Cursor.h"
#include "Map.h"
#include "Referee.h"

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
        Map& _map;
        Referee& _referee;
        APlayer * _opponent;
        float       _timeLimit;

        //Fonction qui calcule le prochain coup
        Stone calc(int depth, float t);
 
        //Fonctions pour le calcul
        int calcMin(Map& map, int depth);
        int calcMax(Map& map, int depth);
 
        //Fonction qui évalue le jeu
        int eval(Map& map);
};
