#include "AI.h"

AI::AI(Map& map, Referee& referee, Stone::E_COLOR color): APlayer(color), _map(map), _referee(referee) {
}

AI::~AI() {

}


//Members
Stone AI::plays() {
    return calc(2);
}

#include <stdlib.h>
int AI::eval(Map& map) {
    return (rand()%50);
}

int AI::calcMax(Map& map, int depth) {
    int tmp;
    int max = -1000;
 
    //Si on est à la profondeur voulue, on retourne l'évaluation
    if (depth == 0)
        return eval(map);
 
    //Si la partie est finie, on retourne l'évaluation de jeu
    // ??
 
    //On parcourt le plateau de jeu et on le joue si la case est vide
    for (int y=1; y<3; ++y)
    {
        for(int x=1; x<3; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                //On joue le coup
                map.placeStone(Stone(y, x, _color));

                tmp = calcMin(map, depth-1);

                if (tmp > max)
                {
                    max = tmp;
                }
                //On annule le coup
                map.removeStone(map[y][x]);
            }
        }
    }
    return max;
}

int AI::calcMin(Map& map, int depth) {
    int tmp;
    int min = 1000;
 
    //Si on est à la profondeur voulue, on retourne l'évaluation
    if (depth == 0)
        return eval(map);
 
    //Si la partie est finie, on retourne l'évaluation de jeu
    // ??
 
    //On parcourt le plateau de jeu et on le joue si la case est vide
    for (int y=1; y<3; ++y)
    {
        for(int x=1; x<3; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                //On joue le coup
                map.placeStone(Stone(y, x, _color));

                tmp = calcMax(map, depth-1);

                if (tmp < min)
                {
                    min = tmp;
                }
                //On annule le coup
                map.removeStone(map[y][x]);
            }
        }
    }
    return min;
}

Stone AI::calc(int depth) {
    int tmp;
    int max = -1000;
    int max_y=-1,max_x=-1;


    Map map_tmp = _map;

    //Si la profondeur est nulle ou la partie est finie,
    //on ne fait pas le calcul et on joue le coup maximal
    if (depth > 0)
    {
        //On parcourt les cases du Goban
        for (int y=0; y<19; ++y)
        {
            for (int x=0; x<19; ++x)
            {
                //Si la case est vide
                if (map_tmp[y][x].getColor() == Stone::E_COLOR::NONE)
                {

                    //On simule qu'on joue cette case
                    map_tmp.placeStone(Stone(y, x, _color));

                    //On appelle la fonction calcMin pour lancer l'IA
                    tmp = calcMin(map_tmp, depth - 1);

                    //Si ce score est plus grand
                    if (tmp > max)
                    {
                        //On le choisit
                        max = tmp;
                        max_y = y;
                        max_x = x;
                    }

                    //On annule le coup
                    map_tmp.removeStone(map_tmp[y][x]);
                }
            }
        }
    }
    std::cout << "IA plays(" << max_y << ";" << max_x << ")" << std::endl;
    return Stone(max_y, max_x, _color);
}