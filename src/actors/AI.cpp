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
        /*while (depth < 10)//TMP, plus tard boucle infinie
            stone = calc(depth++, (float)clock());*/

        stone = calc(2, (float)clock());
    }
    catch (const Exceptions& e)
    {
    }

    if (stone.x() == -1)
        throw Exceptions("AI CAN'T PLAY :(");
    std::cout << "AI depth " << depth-2 << " (starting from 0)" << std::endl;
    return stone;
}

void AI::setTimeLimit(float t)
{
    _timeLimit = t;
}


void AI::setOpponent(APlayer * player) {
    _opponent = player;
}

int AI::eval(Map& map, Referee::E_STATE ret, char captured, char opponentCaptured) {
    int score = 0;

    if (captured - _captured)
    {
        //std::cout << "(c)";
        // std::cout << "Je vais capturer" << std::endl;
        score += captured;
    }
    else if (opponentCaptured - _opponent->getCaptured())
    {
        // std::cout << "Je vais me faire bouffer" << std::endl;
        score -= opponentCaptured;
    }
    else if (ret == Referee::E_STATE::END_WHITE) // TODO : Gerer ca pas en dur
    {
        //std::cout << "(v)";
        // std::cout << "Je vais gagner" << std::endl;
        score = 1000;
    }
    else if (ret == Referee::E_STATE::END_BLACK)
    {
        //std::cout << "(p)";
        // std::cout << "Je vais perdre" << std::endl;
        score = -1000;
    }
    return (score);
}

int AI::calcMax(Map& map, int depth, Referee::E_STATE ret, char& captured, char& opponentCaptured) {
    int tmp;
    int max = -100000;
 
    //Si on est à la profondeur voulue, on retourne l'évaluation
    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
        return eval(map, ret, captured, opponentCaptured);
 
    //Si la partie est finie, on retourne l'évaluation de jeu
    // ??
 
    //On parcourt le plateau de jeu et on le joue si la case est vide
    for (int y=0; y<5; ++y)
    {
        for(int x=0; x<10; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                Map map_tmp = map;
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, tmp_captured);
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMin(map, depth-1, ret, tmp_captured, tmp_opponent_captured);
                    if (tmp > max)
                        max = tmp;
                }
                // //On annule le coup
                // map.removeStone(map[y][x]);
            }
        }
    }
    return max;
}

int AI::calcMin(Map& map, int depth, Referee::E_STATE ret, char& captured, char& opponentCaptured) {
    int tmp;
    int min = 100000;
 
    //Si on est à la profondeur voulue, on retourne l'évaluation
    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
        return eval(map, ret, captured, opponentCaptured);
 
    //Si la partie est finie, on retourne l'évaluation de jeu
    // ??
 
    //On parcourt le plateau de jeu et on le joue si la case est vide
    for (int y=0; y<5; ++y)
    {
        for(int x=0; x<10; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                Map map_tmp = map;
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                Referee::E_STATE ret = _referee.check(Stone(y, x, Referee::OP_COLOR[_color]), map_tmp, tmp_opponent_captured);
                //std::cout << "L'adv joue(" << ret << ")";
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMax(map, depth-1, ret, tmp_captured, tmp_opponent_captured);
                    if (tmp < min)
                        min = tmp;
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
    int max = -100000;
    int max_y=-1,max_x=-1;

    //Si la profondeur est nulle ou la partie est finie,
    //on ne fait pas le calcul et on joue le coup maximal
    if (depth > 0)
    {
        //On parcourt les cases du Goban
        for (int y=0; y<5; ++y)
        {
            if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
                throw Exceptions("AI timeLimitSec exceeded");/* TODO : throw exception ? */
            for (int x=0; x<10; ++x)
            {
                // Copy de la map et du player
                Map map_tmp = _map;
                char tmp_captured = this->getCaptured();
                char tmp_opponent_captured = _opponent->getCaptured();

                Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, tmp_captured);
                //std::cout << "Je joue(" << ret << ")" << std::endl;

                //On appelle la fonction calcMin pour lancer l'IA
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMin(map_tmp, depth - 1, ret, tmp_captured, tmp_opponent_captured);
                    //Si ce score est plus grand
                    if (tmp > max)
                    {
                        //std::cout << "[" << max << "->" << tmp << "]" << std::endl;
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
    return Stone(max_y, max_x, _color);
}