#include "AI.h"
#include "Exceptions.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


AI::AI(Map& map, Referee& referee, Stone::E_COLOR color)
    : APlayer(color, APlayer::AI), _map(map), _referee(referee) {
}

AI::~AI() {

}


//Members
void AI::setTimeLimit(float t)
{
    _timeLimit = t;
}


void AI::setOpponent(APlayer * player) {
    _opponent = player;
}

Stone AI::plays() {
    Stone stone(-1, -1, _color);
    int depth = 1;

    try
    {
        while (true)
        {

            stone = calc(depth++, (float)clock());
        }
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

int AI::eval(Map& map, Referee::E_STATE ret, char captured, char opponentCaptured) {
    char stonesPlayed = map.getPlayed();

    if (ret == Referee::E_STATE::END_WHITE)
        return _color == Stone::E_COLOR::WHITE ? 1000 - stonesPlayed : -1000 + stonesPlayed;
    if (ret == Referee::E_STATE::END_BLACK)
        return _color == Stone::E_COLOR::BLACK ? 1000 - stonesPlayed : -1000 + stonesPlayed;

    int takenStones = captured - _captured;
    int opponentTakenStones = opponentCaptured - _opponent->getCaptured();
    if (takenStones)
        return 100 * takenStones - stonesPlayed;
    if (opponentTakenStones)
        return -100 * opponentTakenStones + stonesPlayed;
    return (0);
}


int AI::calcMax(Map& map, int depth, float t, Referee::E_STATE ret, char& captured, char& opponentCaptured) {
    int score;
    int max = -100000;
 
    //On parcourt les cases du Goban
    for (int y = 0; y < Map::_MAPSIZE_Y; ++y)
    {
        for (int x = 0; x < Map::_MAPSIZE_X; ++x)
        {
            // On vérifie si on a pas dépassé le temps maximal
            if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
                throw Exceptions("AI timeLimitSec exceeded");

            // On joue seulement si une pierre n'est pas déja présente
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                // Copy de la map et des nombres de pierres capturées
                Map map_tmp = map;
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                // On crée la pierre et on joue le coup
                Stone stone = Stone(y, x, _color);
                Referee::E_STATE ret = _referee.check(stone, map_tmp, tmp_captured);

                // Si le coup est valide on évalue (Pas de double trois)
                if (ret != Referee::E_STATE::INVALID)
                {
                    //Si on est à la profondeur voulue ou que la partie est finie, on retourne l'évaluation
                    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
                        score = eval(map, ret, captured, opponentCaptured);
                    else
                        score = calcMin(map_tmp, depth-1, t, ret, tmp_captured, tmp_opponent_captured);

                    // Si le score est plus petit on le sauvegarde
                    if (score > max)
                        max = score;
                }
                // On annule le coup (Ici rien pour l'instant car copie de la Map et des éléments)
            }
        }
    }
    return max;
}

int AI::calcMin(Map& map, int depth, float t, Referee::E_STATE ret, char& captured, char& opponentCaptured) {
    int score;
    int min = 100000;

    //On parcourt les cases du Goban
    for (int y = 0; y < Map::_MAPSIZE_Y; ++y)
    {
        for (int x = 0; x < Map::_MAPSIZE_X; ++x)
        {
            // On vérifie si on a pas dépassé le temps maximal
            if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
                throw Exceptions("AI timeLimitSec exceeded");

            // On joue seulement si une pierre n'est pas déja présente
            if (map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                // Copy de la map et des nombres de pierres capturées
                Map map_tmp = map;
                char tmp_captured = captured;
                char tmp_opponent_captured = opponentCaptured;

                // On crée la pierre et on joue le coup
                Stone stone = Stone(y, x, Referee::OP_COLOR[_color]);
                Referee::E_STATE ret = _referee.check(stone, map_tmp, tmp_opponent_captured);

                // Si le coup est valide on évalue (Pas de double trois)
                if (ret != Referee::E_STATE::INVALID)
                {
                    //Si on est à la profondeur voulue ou que la partie est finie, on retourne l'évaluation
                    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
                        score = eval(map, ret, captured, opponentCaptured);
                    else
                        score = calcMax(map_tmp, depth-1, t, ret, tmp_captured, tmp_opponent_captured);

                    // Si le score est plus petit on le sauvegarde
                    if (score < min)
                        min = score;
                }
                // On annule le coup (Ici rien pour l'instant car copie de la Map et des éléments)
            }
        }
    }
    return min;
}

Stone AI::calc(int depth, float t) {
    int score;
    int max_y=-1,max_x=-1;
    int max = -10000;

    //On parcourt les cases du Goban
    for (int y=0; y<Map::_MAPSIZE_Y; ++y)
    {
        for (int x=0; x<Map::_MAPSIZE_X; ++x)
        {
            // On vérifie si on a pas dépassé le temps maximal
            if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
                throw Exceptions("AI timeLimitSec exceeded");

            // On joue seulement si une pierre n'est pas déja présente
            if (_map[y][x].getColor() == Stone::E_COLOR::NONE)
            {
                // Copy de la map et des nombres de pierres capturées
                Map map_tmp = _map;
                char tmp_captured = this->getCaptured();
                char tmp_opponent_captured = _opponent->getCaptured();

                // On crée la pierre et on joue le coup
                Stone stone = Stone(y, x, _color);
                Referee::E_STATE ret = _referee.check(stone, map_tmp, tmp_captured);

                // Si le coup est valide on évalue (Pas de double trois)
                if (ret != Referee::E_STATE::INVALID)
                {
                    //Si on est à la profondeur voulue ou que la partie est finie, on retourne l'évaluation
                    if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
                        score = eval(map_tmp, ret, tmp_captured, tmp_opponent_captured);
                    // Sinon on continue
                    else
                        score = calcMin(map_tmp, depth - 1, t, ret, tmp_captured, tmp_opponent_captured/*, alpha, beta*/);

                    // Si ce score est plus grand
                    if (score > max)/*Moins optimise mais aleatoire: if (score > max || (score == max && rand()%2))*/
                    {
                        std::cout << "depth:"<<depth<<"[" << max << "("<<max_y<<";"<<max_x<<")->" << score << "("<<y<<";"<<x<< ")]" << std::endl;
                        //On le choisit
                        max = score;
                        // On sauvegarde les coordonnées du coup optimum
                        max_y = y;
                        max_x = x;
                    }
                }
                // On annule le coup (Ici rien pour l'instant car copie de la Map et des éléments)
            }
        }
    }
    // On retourne la pierre optimale
    return Stone(max_y, max_x, _color);
}













// int AI::calcMinMax(Map& map, int depth, float t, Referee::E_STATE ret, Stone::E_COLOR color, int alpha, int beta) {
//     if (depth == 0 || ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
//          return eval(map, ret);

//     //On parcourt le plateau de jeu et on joue si la case est vide
//     for (int y = 0; y < Map::_MAPSIZE_Y; ++y)
//     {
//         for (int x = 0; x < Map::_MAPSIZE_X; ++x)
//         {
//             if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
//                 throw Exceptions("AI timeLimitSec exceeded");

//             if (map[y][x].getColor() == Stone::E_COLOR::NONE)
//             {
//                 // Copy de la map
//                 Map map_tmp = map;
//                 char fake_captured = 0;

//                 Stone stone = Stone(y, x, color);
//                 Referee::E_STATE ret = _referee.check(stone, map_tmp, fake_captured);
//                 if (ret != Referee::E_STATE::INVALID)
//                 {
//                     int tmp = -calcMinMax(map_tmp, depth-1, t, ret, Referee::OP_COLOR[color], -beta, -alpha);
//                     // if (tmp > alpha)
//                     //     alpha = tmp;
//                     // if (alpha >= beta)
//                         return alpha;
//                 }
//                 // On annule le coup
//             }
//         }
//     }
//     return alpha;
// }

// Stone AI::calc(int depth, float t) {
//     int max_y = -1;
//     int max_x = -1;
//     int alpha = -100000;
//     int beta = 100000;

//     //On parcourt les cases du Goban
//     for (int y = 0; y < Map::_MAPSIZE_Y; ++y)
//     {
//         for (int x = 0; x < Map::_MAPSIZE_X; ++x)
//         {
//             if (((float)clock() / CLOCKS_PER_SEC) - (t / CLOCKS_PER_SEC) > _timeLimit)
//                 throw Exceptions("AI timeLimitSec exceeded");

//             // Copy de la map
//             Map map_tmp = _map;
//             char fake_captured = 0;

//             Stone stone = Stone(y, x, _color);
//             Referee::E_STATE ret = _referee.check(stone, map_tmp, fake_captured);
//             if (ret != Referee::E_STATE::INVALID)
//             {
//                 int tmp = calcMinMax(map_tmp, depth - 1, t, ret, Referee::OP_COLOR[_color], beta, alpha);
//                 if (tmp != 0 && tmp != 1 && tmp != -1)
//                     std::cout << "tmp:"<<tmp << std::endl;
//                 //Si ce score est plus grand
// /*                if (tmp > alpha)
//                 {*/
//                     std::cout << "depth:"<<depth<<"[" << alpha << "("<<max_y<<";"<<max_x<<")->" << tmp << "("<<y<<";"<<x<< ")]" << std::endl;
//                     alpha = tmp;
//                     max_y = y;
//                     max_x = x;
//                 // }
//             }
//             // On annule le coup
//             }
//     }
//     return Stone(max_y, max_x, _color);
// }


