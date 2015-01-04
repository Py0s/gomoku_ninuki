#include "AI.h"
#include "Exceptions.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


AI::AI(Map& map, Referee& referee, Stone::E_COLOR color)
    : APlayer(color, APlayer::AI), _map(map), _referee(referee) {
}

AI::~AI() {

}


//Members
void AI::setTimeLimit(float durationSeconds)
{
    _durationSeconds = durationSeconds;
}
void AI::setOpponent(APlayer * player) {
    // _opponent = player;
    // _opColor = player->getColor();
}


inline void        AI::checkTime() {
    if (((float)clock() / CLOCKS_PER_SEC) - (_playBeginTime / CLOCKS_PER_SEC) > _durationSeconds)
        throw Exceptions("AI timeLimitSec exceeded");
}

Stone AI::plays() {
    Stone stone(-1, -1, _color);
    int depth = 1;

    initOpenTiles();
    try
    {
        _playBeginTime = (float)clock();
        while (true)
        {
            stone = calc(depth++);
        }
    }
    catch (const Exceptions& e)
    {
        depth -= 1;
    }

    if (stone.x() == -1)
        throw Exceptions("AI CAN'T PLAY :(");//TODO : catch + haut
    std::cout << "AI depth " << depth-1 << std::endl;
    return stone;
}

Stone AI::helpMe(Stone::E_COLOR color) {
    _color = color;
    Stone stone(-1, -1, color);

    initOpenTiles();
    try
    {
        _playBeginTime = (float)clock();
        stone = calc(2);
    }
    catch (const Exceptions& e)
    {
    }

    if (stone.x() == -1)
        throw Exceptions("AI CAN'T PLAY :(");//TODO : catch + haut
    std::cout << "AI help depth " << 2 << std::endl;
    return stone;
}

int AI::eval(Map& map, Referee::E_STATE ret, Stone::E_COLOR color) {
    // char stonesPlayed = map.getPlayed();

    if (ret == Referee::COLOR_WIN[color])//si j'ai gagne
        return 1000/* - map.getPlayed()*/;
    if (ret == Referee::COLOR_WIN[Referee::OP_COLOR[color]])//si l'adversaire a gagne
        return /*map.getPlayed()*/ - 1000;

    if (ret == Referee::END_DRAW)//si match null
        return 0;

    // int takenStones =  map.getCapturedBy(color) - (color == _color ? _captured : _opponent->getCaptured());
    // int opponentTakenStones = map.getCapturedBy(Referee::OP_COLOR[color]) - (color == _color ? _captured : _opponent->getCaptured());
    // if (takenStones)
    //     return 100 * takenStones - stonesPlayed;
    // if (opponentTakenStones)
    //     return -100 * opponentTakenStones + stonesPlayed;
    return (map.getCapturedBy(color) - map.getCapturedBy(Referee::OP_COLOR[color]));
}

int AI::getEvalForFirstMovePossible(Map& map, int depth, Stone::E_COLOR color, int alpha, int beta,
                                    int &y, int &x) {

    // On parcours le Goban a la recherche du premier coup possible
    for (; y < Map::_MAPSIZE_Y; ++y)
    {
        for (; x < Map::_MAPSIZE_X; ++x)
        {
            checkTime();

            if (map[y][x].isEmpty())
            {
                // Copy de la map et des nombres de pierres capturées
                Map map_tmp = map;

                // On crée la pierre et on joue le coup
                char fake = 0;
                Referee::E_STATE ret = _referee.check(Stone(y, x, color), map_tmp, fake);

                // Si le coup est valide on évalue (Pas de double trois)
                if (ret != Referee::INVALID)
                    return -calcMinMax(map_tmp, depth-1, ret, Referee::OP_COLOR[color], -beta, -alpha);
            }
        }
    }
    return 0;
}

int AI::calcMinMax(Map& map, int depth, Referee::E_STATE ret, Stone::E_COLOR color, int alpha, int beta) {

    if (depth == 0 || Referee::gameHasEnded(ret))
        return eval(map, ret, color);

    // int y_first = 0;
    // int x_first = 0;

    // On récupère l'évaluation du premier coup possible
    // int current = getEvalForFirstMovePossible(map, depth, color, alpha, beta, y_first, x_first);
    // if (current >= alpha)
    //     alpha = current;

    // if (current < beta)
    // {
        TILE_IT_T it = _openTiles.begin();
        // On parcours les autres cases du Goban
        while (it != _openTiles.end()) {
            checkTime();
            int y = it->first;//le temps de faire marcher les iterateurs
            int x = it->second;

            // Copy de la map et des nombres de pierres capturées
            Map map_tmp = map;
            // On crée la pierre et on joue le coup
            char fake = 0;
            Referee::E_STATE ret = _referee.check(Stone(y, x, color), map_tmp, fake);
            // Si le coup est valide on évalue (Pas de double trois)
            if (ret != Referee::INVALID)
            {
                // int score = 1;
                int score = -calcMinMax(map_tmp, depth-1, ret, Referee::OP_COLOR[color], -(alpha+1), -alpha);
                if (score > alpha && score < beta)
                    score = -calcMinMax(map_tmp, depth-1, ret, Referee::OP_COLOR[color], -beta, -alpha);
                // if (score >= current)
                // {
                    // current = score;
                    if (score >= alpha)
                    {
                        alpha = score;
                        if (/*alpha*/score >= beta)
                            return score;
                            // return current;
                    }
                // }
            }
            ++it;
        }
    // }
    return alpha;
    // return /*alpha*/current;
}

Stone AI::calc(int depth) {
    int score;
    int max_y=-1,max_x=-1;
    //int max = -AI_INFINITY;
    int alpha = -AI_INFINITY;
    int beta = AI_INFINITY;

    //On parcourt les cases du Goban
    TILE_IT_T it = _openTiles.begin();
    while (it != _openTiles.end()) {
        checkTime();
        int y = it->first;//le temps de faire marcher les iterateurs
        int x = it->second;

        Map map_tmp = _map;// Copy de la map et des nombres de pierres capturées

        char fake = 0;// On crée la pierre et on joue le coup
        Referee::E_STATE ret = _referee.check(Stone(y,x, _color), map_tmp, fake);

        // _closeTiles.push_back(*it);
        // it = _openTiles.erase(it);
        // Si le coup est valide on évalue (Pas de double trois)
        if (ret != Referee::INVALID)
        {
            //score = calcMin(map_tmp, depth - 1, ret, alpha, beta);
            
            score = -calcMinMax(map_tmp, depth - 1, ret, Referee::OP_COLOR[_color], -beta, -alpha);
            // Si ce score est plus grand
            //if (score > max)/*Moins optimise mais aleatoire: if (score > max || (score == max && rand()%2))*/
            if (score > alpha)
            {
                std::cout << "depth:"<<depth<<"[" << alpha << "("<<max_y<<";"<<max_x<<")->" << score << "("<<y<<";"<<x<< ")]" << std::endl;
                //On le choisit
                //max = score;
                alpha = score;
                // On sauvegarde les coordonnées du coup optimum
                max_y = y;
                max_x = x;
            }
        }
        // On annule le coup (Ici rien pour l'instant car copie de la Map et des éléments)
        // TILE_VALUE_T tmp_tile = _closeTiles.back();
        // _closeTiles.pop_back();
        // it = _openTiles.insert(it, tmp_tile);
        ++it;
    }
    // On retourne la pierre optimale
    return Stone(max_y, max_x, _color);
}

//Stone AI::calc(int depth) {
//    
//}


void AI::initOpenTiles() {
    _openTiles.clear();
    _closeTiles.clear();//?
    int i = 0;
    for (int y=0; y<Map::_MAPSIZE_Y; ++y) {
        for (int x=0; x<Map::_MAPSIZE_X; ++x) {
            if (_map[y][x].isEmpty()) {
                _openTiles.push_back(std::pair<int,int>(y,x)/*_map[y][x]*/);//TODO : remettre ?
                //std::cout << "OPEN ? : "<< y << " " << x << std::endl;
                //std::cout << "OPEN : "<< i << _openTiles[i].first << " " << _openTiles[i].second << std::endl;
                i++;
            }
        }
    }
}
// void AI::initOpenTilesDebug(Map& map) {
//     _openTiles.clear();
//     _closeTiles.clear();//?
//     for (int y=0; y<Map::_MAPSIZE_Y; ++y) {
//         for (int x=0; x<Map::_MAPSIZE_X; ++x) {
//             if (map[y][x].isEmpty()) {
//                 _openTiles.push_back(map[y][x]);
//             }
//         }
//     }
// }
inline void AI::closeTile(TILE_IT_T & it) {
    _closeTiles.push_back(*it);
    it = _openTiles.erase(it);    
}



// int AI::eval(Map& map, Referee::E_STATE ret, char captured, char opponentCaptured) {
//     char stonesPlayed = map.getPlayed();

//     if (ret == Referee::END_WHITE)
//         return _color == Stone::WHITE ? 1000 - stonesPlayed : -1000 + stonesPlayed;
//     if (ret == Referee::END_BLACK)
//         return _color == Stone::BLACK ? 1000 - stonesPlayed : -1000 + stonesPlayed;

//     int takenStones = captured - _captured;
//     int opponentTakenStones = opponentCaptured - _opponent->getCaptured();
//     if (takenStones)
//         return 100 * takenStones - stonesPlayed;
//     if (opponentTakenStones)
//         return -100 * opponentTakenStones + stonesPlayed;
//     return (0);
// }

// int AI::eval(Map& map, Referee::E_STATE ret) {
//     char stonesPlayed = map.getPlayed();

//     if (ret == Referee::END_WHITE)
//         return _color == Stone::WHITE ? 1000 - stonesPlayed : -1000 + stonesPlayed;
//     if (ret == Referee::END_BLACK)
//         return _color == Stone::BLACK ? 1000 - stonesPlayed : -1000 + stonesPlayed;

//     int takenStones = map.getCapturedBy(_color) - _captured;
//     int opponentTakenStones = map.getCapturedBy(_opColor) - _opponent->getCaptured();
//     if (takenStones)
//         return 100 * takenStones - stonesPlayed;
//     if (opponentTakenStones)
//         return -100 * opponentTakenStones + stonesPlayed;
//     return (0);
// }

// int AI::calcMax(Map& map, int depth, Referee::E_STATE ret, int alpha, int beta) {

//     if (depth == 0 || Referee::gameHasEnded(ret))
//         return eval(map, ret);

//     int score;
//     //int max = -AI_INFINITY;

//     //On parcourt les cases du Goban
//     for (int y = 0; y < Map::_MAPSIZE_Y; ++y)
//     {
//         for (int x = 0; x < Map::_MAPSIZE_X; ++x)
//         {
//             checkTime();

//             if (map[y][x].isEmpty())
//             {
//                 // Copy de la map et des nombres de pierres capturées
//                 Map map_tmp = map;

//                 // On crée la pierre et on joue le coup
//                 char fake = 0;
//                 Referee::E_STATE ret = _referee.check(Stone(y, x, _color), map_tmp, fake);

//                 // Si le coup est valide on évalue (Pas de double trois)
//                 if (ret != Referee::INVALID)
//                 {
//                     score = calcMin(map_tmp, depth-1, ret, alpha, beta);

//                     // Si le score est plus petit on le sauvegarde
//                     // if (score > max)
//                     //     max = score;
//                     if (score > alpha)
//                     {
//                         alpha = score;
//                         if (alpha >= beta)
//                             return alpha;
//                     }
//                 }
//                 // On annule le coup (Ici rien pour l'instant car copie de la Map et des éléments)
//             }
//         }
//     }
//     //return max;
//     return alpha;
// }

// int AI::calcMin(Map& map, int depth, Referee::E_STATE ret, int alpha, int beta) {

//     if (depth == 0 || Referee::gameHasEnded(ret))
//         return eval(map, ret);

//     int score;
//     //int min = AI_INFINITY;

//     //On parcourt les cases du Goban
//     for (int y = 0; y < Map::_MAPSIZE_Y; ++y)
//     {
//         for (int x = 0; x < Map::_MAPSIZE_X; ++x)
//         {
//             checkTime();

//             if (map[y][x].isEmpty())
//             {
//                 // Copy de la map et des nombres de pierres capturées
//                 Map map_tmp = map;

//                 // On crée la pierre et on joue le coup
//                 char fake = 0;
//                 Referee::E_STATE ret = _referee.check(Stone(y, x, _opColor), map_tmp, fake);

//                 // Si le coup est valide on évalue (Pas de double trois)
//                 if (ret != Referee::INVALID)
//                 {
//                     score = calcMax(map_tmp, depth-1, ret, alpha, beta);

//                     // Si le score est plus petit on le sauvegarde
//                     // if (score < min)
//                     //     min = score;
//                     if (score < beta)
//                     {
//                         beta = score;
//                         if (beta <= alpha)
//                             return beta;
//                     }
//                 }
//                 // On annule le coup (Ici rien pour l'instant car copie de la Map et des éléments)
//             }
//         }
//     }
//     //return min;
//     return beta;
// }
