#include "AI.h"
#include "Exceptions.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


AI::AI(Map& map, Referee& referee, Stone::E_COLOR color): APlayer(color), _map(map), _referee(referee) {
}

AI::~AI() {

}

// /* clock example: frequency of primes */
// #include <stdio.h>      /* printf */
// #include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
// #include <math.h>       /* sqrt */

// int frequency_of_primes (int n) {
//   int i,j;
//   int freq=n-1;
//   for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
//   return freq;
// }

// int main ()
// {
//   clock_t t;
//   int f;
//   t = clock();
//   printf ("Calculating...\n");
//   f = frequency_of_primes (99999);
//   printf ("The number of primes lower than 100,000 is: %d\n",f);
//   t = clock() - t;
//   printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
//   return 0;
// }

//Members
Stone AI::plays() {
    Stone stone(-1, -1, _color);
    int depth = 0;

    try
    {
        while (depth < 10)//TMP, plus tard boucle infinie
            stone = calc(depth++, (float)clock());
    }
    catch (const Exceptions& e)
    {
    }

    if (stone.x() == -1)
        throw Exceptions("AI CAN'T PLAY :(");
    std::cout << "AI depth " << depth-1 << " (starting from 0)" << std::endl;
    return stone;
}

void AI::setTimeLimit(float t)
{
    _timeLimit = t;
}


void AI::setOpponent(APlayer * player) {
    _opponent = player;
}

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
    for (int y=0; y<19; ++y)
    {
        for(int x=0; x<19; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                Map map_tmp = map;
                char tmp_capturedStones = this->getCapturedStones();

                Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, tmp_capturedStones);
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMin(map, depth-1);
                    if (tmp > max)
                    {
                        max = tmp;
                    }
                }
                // //On annule le coup
                // map.removeStone(map[y][x]);
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
    for (int y=0; y<19; ++y)
    {
        for(int x=0; x<19; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                Map map_tmp = map;
                char tmp_capturedStones = _opponent->getCapturedStones();

                Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, tmp_capturedStones);
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMax(map, depth-1);
                    if (tmp < min)
                    {
                        min = tmp;
                    }
                }
                // //On annule le coup
                // map.removeStone(map[y][x]);
            }
        }
    }
    return min;
}

Stone AI::calc(int depth, float t) {
    int tmp;
    int max = -1000;
    int max_y=-1,max_x=-1;

    //Si la profondeur est nulle ou la partie est finie,
    //on ne fait pas le calcul et on joue le coup maximal
    if (depth > 0)
    {
        //On parcourt les cases du Goban
        for (int y=0; y<19; ++y)
        {
            if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
                throw Exceptions("AI timeLimitSec exceeded");/* TODO : throw exception ? */
            for (int x=0; x<19; ++x)
            {
                // Copy de la map et du player
                Map map_tmp = _map;
                char tmp_capturedStones = this->getCapturedStones();

                Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, tmp_capturedStones);

                //On appelle la fonction calcMin pour lancer l'IA
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMin(map_tmp, depth - 1);
                    //Si ce score est plus grand
                    if (tmp > max)
                    {
                        //On le choisit
                        max = tmp;
                        max_y = y;
                        max_x = x;
                    }
                }
                // //On annule le coup
                // map_tmp.removeStone(map_tmp[y][x]);
                }
        }
    }
    std::cout << "IA plays(" << max_y << ";" << max_x << ")" << std::endl;
    return Stone(max_y, max_x, _color);
}