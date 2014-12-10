#include "AI.h"
#include "Exceptions.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


AI::AI(Map& map, Referee& referee, Stone::E_COLOR color)
    : APlayer(color, APlayer::AI), _map(map), _referee(referee) {
}

AI::~AI() {

}


//Members
Stone AI::plays() {
    Stone stone(-1, -1, _color);
    int depth = 1;

    try
    {
        while (42)
            stone = calc(depth++, (float)clock());
    }
    catch (const Exceptions& e)
    {
        depth -= 1;
    }

    if (stone.x() == -1)
        throw Exceptions("AI CAN'T PLAY :(");
    std::cout << "AI depth " << depth-1 << std::endl;
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
        score = 500 - map.getPlayed();
    }
    else if (opponentCaptured - _opponent->getCaptured())
    {
        // std::cout << "Je vais me faire bouffer" << std::endl;
        score = -500 + map.getPlayed();
    }
    else if (ret == Referee::E_STATE::END_WHITE) // TODO : Gerer ca pas en dur
    {
        //std::cout << "(v)";
        // std::cout << "Je vais gagner" << std::endl;
        score = 1000 - map.getPlayed();
    }
    else if (ret == Referee::E_STATE::END_BLACK)
    {
        //std::cout << "(p)";
        // std::cout << "Je vais perdre" << std::endl;
        score = -1000 + map.getPlayed();
    }
    return (score);
}

int AI::calcMax(Map& map, int depth, Referee::E_STATE ret, char& captured, char& opponentCaptured, int alpha, int beta) {
    int tmp;
    //int max = -100000;
 
    //Si on est à la profondeur voulue ou que la partie est finie, on retourne l'évaluation
    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
        return eval(map, ret, captured, opponentCaptured);
 
    //On parcourt le plateau de jeu et on joue si la case est vide
    for (int y=0; y<Map::_MAPSIZE_Y; ++y)
    {
        for(int x=0; x<Map::_MAPSIZE_X; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                // Copy de la map et des nombres de pierres capturées
                Map map_tmp = map;
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                Stone stone = Stone(y, x, _color);
                Referee::E_STATE ret = _referee.check(stone, map_tmp, tmp_captured);
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMin(map_tmp, depth-1, ret, tmp_captured, tmp_opponent_captured, alpha, beta);
                    if (tmp > alpha)
                        alpha = tmp;
                    if (beta <= alpha)
                        return alpha;
                }
                // On annule le coup
            }
        }
    }
    return alpha;
}

int AI::calcMin(Map& map, int depth, Referee::E_STATE ret, char& captured, char& opponentCaptured, int alpha, int beta) {
    int tmp;
    //int min = 100000;
 
    //Si on est à la profondeur voulue ou que la partie est finie, on retourne l'évaluation
    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
        return eval(map, ret, captured, opponentCaptured);
 
    //On parcourt le plateau de jeu et on joue si la case est vide
    for (int y=0; y<Map::_MAPSIZE_Y; ++y)
    {
        for(int x=0; x<Map::_MAPSIZE_X; ++x)
        {
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                // Copy de la map et des nombres de pierres capturées
                Map map_tmp = map;
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                Stone stone = Stone(y, x, Referee::OP_COLOR[_color]);
                Referee::E_STATE ret = _referee.check(stone, map_tmp, tmp_opponent_captured);
                //std::cout << "L'adv joue(" << ret << ")";
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMax(map, depth-1, ret, tmp_captured, tmp_opponent_captured, alpha, beta);
                    if (tmp < beta)
                        beta = tmp;
                    if (beta <= alpha)
                        return beta;
                }
                // On annule le coup
            }
        }
    }
    return beta;
}

Stone AI::calc(int depth, float t) {
    int tmp;
    int max = -100000;
    int max_y=-1,max_x=-1;
    int alpha = -100000;
    int beta = 100000;

    //On parcourt les cases du Goban
    for (int y=0; y<Map::_MAPSIZE_Y; ++y)
    {
        for (int x=0; x<Map::_MAPSIZE_X; ++x)
        {
            if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
                throw Exceptions("AI timeLimitSec exceeded");

            // Copy de la map et des nombres de pierres capturées
            Map map_tmp = _map;
            char tmp_captured = this->getCaptured();
            char tmp_opponent_captured = _opponent->getCaptured();

            Stone stone = Stone(y, x, _color);
            Referee::E_STATE ret = _referee.check(stone, map_tmp, tmp_captured);
            //std::cout << "Je joue(" << ret << ")" << std::endl;

            //On appelle la fonction calcMin pour lancer l'IA
            if (ret != Referee::E_STATE::INVALID)
            {
                tmp = calcMin(map_tmp, depth - 1, ret, tmp_captured, tmp_opponent_captured, alpha, beta);
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
            // On annule le coup
            }
    }
    return Stone(max_y, max_x, _color);
}