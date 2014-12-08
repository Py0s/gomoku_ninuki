#include "AI.h"

AI::AI(Map& map, Referee& referee, Stone::E_COLOR color): APlayer(color), _map(map), _referee(referee) {
}

AI::~AI() {

}


//Members
Stone AI::plays() {
    return calc(3);
}


void AI::setOpponent(APlayer * player) {
    _opponent = player;
}

int AI::eval(Map& map, Referee::E_STATE ret, char captured, char opponentCaptured) {
    int score = 0;

    if (captured - _captured)
    {
        // std::cout << "Je vais capturer" << std::endl;
        score += captured;
    }
    else if (opponentCaptured - _opponent->getCaptured())
    {
        // std::cout << "Je vais me faire bouffer" << std::endl;
        score -= opponentCaptured;
    }
    if (ret == Referee::E_STATE::END_WHITE) // TODO : Gerer ca pas en dur
    {
        // std::cout << "Je vais gagner" << std::endl;
        score += 500;
    }
    else if (ret == Referee::E_STATE::END_BLACK)
    {
        // std::cout << "Je vais perdre" << std::endl;
        score -= 500;   
    }
    return (score);
}

int AI::calcMax(Map& map, int depth, Referee::E_STATE ret, char& captured, char& opponentCaptured) {
    int tmp;
    int max = -1000;
 
    //Si on est à la profondeur voulue, on retourne l'évaluation
    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
        return eval(map, ret, captured, opponentCaptured);
 
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
    int min = 1000;
 
    //Si on est à la profondeur voulue, on retourne l'évaluation
    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
        return eval(map, ret, captured, opponentCaptured);
 
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
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                Referee::E_STATE ret = _referee.check(Stone(y, x, Referee::OP_COLOR[_color]), map_tmp, tmp_opponent_captured);
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

Stone AI::calc(int depth) {
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
            for (int x=0; x<19; ++x)
            {
                // Copy de la map et du player
                Map map_tmp = _map;
                char tmp_captured = this->getCaptured();
                char tmp_opponent_captured = _opponent->getCaptured();

                Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, tmp_captured);

                //On appelle la fonction calcMin pour lancer l'IA
                if (ret != Referee::E_STATE::INVALID)
                {
                    tmp = calcMin(map_tmp, depth - 1, ret, tmp_captured, tmp_opponent_captured);
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
    return Stone(max_y, max_x, _color);
}