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

    private:
        Map& _map;
        Referee& _referee;

        //Fonction qui calcule le prochain coup
        Stone calc(int depth);
 
        //Fonctions pour le calcul
        int calcMin(Map& map, int depth);
        int calcMax(Map& map, int depth);
 
        //Fonction qui évalue le jeu
        int eval(Map& map);
};
