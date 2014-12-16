
#include "Stone.h"
#include "Referee.h"
#include "ExcOutOfBound.h"
#include "Game.h"
#include <assert.h>

const enum Stone::E_COLOR Referee::OP_COLOR[] = { Stone::WHITE, Stone::BLACK };

Referee::Referee(): _conf(nullptr) {
}

Referee::~Referee() {

}

// Setters
void Referee::setConf(Config const * conf) {
    this->_conf = conf;
}

// Members
Referee::E_STATE Referee::check(const Stone& s, Map& map, char& captured) {
    assert(this->_conf != nullptr);
    Tile& tile = map[s.y()][s.x()];

    // TODO : mettre ça avant l'appel a check
    if (tile.getColor() != Stone::E_COLOR::NONE)
        return INVALID;

    map.placeStone(s);
    map.played();// TODO : pourquoi c'est pas direct dans placeStones ?

    // if RULE
    if (checkDoubleThree(map, tile, s.color()))
    {
        map.removeStone(tile);
        //TODO : ya pas de played-- ?
        return INVALID;
    }

    if (checkCapture(tile, map, captured))
    {
        if (tile.getColor() == Stone::E_COLOR::BLACK)
            return END_BLACK;
        return END_WHITE;
    }
    E_STATE ret = checkAlign(tile, map, this->_conf->fivebreak_rule);
    if (ret == Referee::E_STATE::END_WHITE || ret == Referee::E_STATE::END_BLACK)
    {
        std::cout << "Ref ret:"<<ret << std::endl;
        map.displayDebug();
    }
    
    if (this->_conf->fivebreak_rule == true && ret != END_BLACK && ret != END_WHITE)
    {
        // Recheck des alignements potentiellement gagnants mais cassables
        ret = checkLbreakables(map);
    }
    // map.displayDebug();

    if (map.getPlayed() == MAX_STONE_PLAYED)
        return END_DRAW;

    return ret;
}

/* DOUBLE THREE FUNCTIONS */
bool Referee::alignOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, 1);

    if (inter_tile.getIntValue(color, dir % 4) == 3)
        return true;
    return false;
}

bool Referee::XFactorextrem(Map& map, Tile& tile, Stone::E_COLOR color, int dir, int first_value, int second_value) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, first_value);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    Tile& second_inter_tile = (map.*ptr)(tile, second_value);

    if (second_inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}

bool Referee::alignTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, tile.getValue(color, dir) + 1);

    if (inter_tile.getIntValue(color, dir) == 3)
        return true;
    return false;
}

bool Referee::alignThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    return true;
}

bool Referee::checkFreeThreeConfig(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    try
    {
        switch (tile.getIntValue(color, dir))
        {
            case 1:
                if (alignOne(map, tile, color, dir)
                    && /*extremOne(map, tile, color, dir))*/  XFactorextrem(map, tile, color, dir, 4, 1))
                {
                    // std::cout << "Cas 1 align" << std::endl;
                    return true;
                }
                break;
            case 2:
                if (alignTwo(map, tile, color, dir)
                    && /*extremTwo(map, tile, color, dir))*/ XFactorextrem(map, tile, color, dir, tile.getValue(color, dir) + 3, tile.getValue(color, Map::OP_DIR[dir]) + 1))
                {
                    // std::cout << "Cas 2 align" << std::endl;
                    return true;
                }
                break;
            case 3:
                if (alignThree(map, tile, color, dir)
                    && /*extremThree(map, tile, color, dir))*/ XFactorextrem(map, tile, color, dir, tile.getValue(color, dir) + 1, tile.getValue(color, Map::OP_DIR[dir]) + 1)) // TODO : OPTI POUR NE PAS CHECKER DEUX FOIS LA MEME CHOSE
                {
                    // std::cout << "Cas 3 align" << std::endl;
                    return true;
                }
                break;
            default:
                break;
        }
    }
    catch (const ExcOutOfBound& e) {
        return false;
    }
    return false;
}

bool Referee::checkDoubleThreeSecondPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
{
    for (int second_dir = 0; second_dir < 8; ++second_dir)
    {
        if (first_dir != second_dir
            && Map::OP_DIR[first_dir] != second_dir)
        {
            // std::cout << "On va checker si 2e trois libre:" << second_dir << std::endl;
            if (checkFreeThreeConfig(map, tile, color, second_dir))
                return true;
        }
    }
    return false;
}


bool Referee::XFactorParcours(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir, int first_value, int second_value) const
{
    Map::PTR ptr = map.go[first_dir];

    if (checkDoubleThreeSecondPart(map, tile, color, first_dir))
        return true;

    Tile& second_tile = (map.*ptr)(tile, first_value);
    if (checkDoubleThreeSecondPart(map, second_tile, color, first_dir))
        return true;

    Tile& third_tile = (map.*ptr)(tile, second_value);
    if (checkDoubleThreeSecondPart(map, third_tile, color, first_dir))
        return true;

    return false;
}

bool Referee::alignParcours(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
{
    try
    {
        switch (tile.getIntValue(color, first_dir))
        {
            case 1:
                if (XFactorParcours(map, tile, color, first_dir, 2, 3) == true) /*if (parcoursOne(map, tile, color, first_dir) == true)*/
                    return true;
                break;
            case 2:
                if (XFactorParcours(map, tile, color, first_dir, 1, 3) == true) /*if (parcoursTwo(map, tile, color, first_dir) == true)*/
                    return true;
                break;
            case 3:
                if (XFactorParcours(map, tile, color, first_dir, 1, 2) == true) /*if (parcoursThree(map, tile, color, first_dir) == true)*/
                    return true;
                break;
            default:
                break;
        }
    }
    catch (const ExcOutOfBound& e) {
        return false;
    }
    return false;
}

bool Referee::checkDoubleThreeFirstPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
{
    if (checkFreeThreeConfig(map, tile, color, first_dir))
    {
        // std::cout << "Premier trois libre" << std::endl;

        if (alignParcours(map, tile, color, first_dir) == true)
            return true;

        // PARCOURIR TOUTES LES PIERRES DE L ALIGNEMENT
        // {
        //     if (checkDoubleThreeSecondPart(map, tile, color, first_dir))
        //         return true;
        // }
    }
    return false;
}

bool Referee::checkDoubleThree(Map& map, Tile& tile, Stone::E_COLOR color) const
{
    for (int first_dir = 0; first_dir < 8; ++first_dir)
    {
        if (checkDoubleThreeFirstPart(map, tile, color, first_dir))
            return true;
    }
    return false;
}

/* CAPTURE FUNCTIONS */
bool Referee::checkCapture(Tile& tile, Map& map, char& captured) const {
    Stone::E_COLOR color = tile.getColor();

    for (int dir = 0; dir < 8; ++dir)
    {
        if (map[tile.Y][tile.X].getValue(Referee::OP_COLOR[color], dir) == 2)
        {
            try
            {
                Map::Map::PTR ptr = map.go[dir];
                Tile& tile_for_capture = (map.*ptr)(tile, 3);

                if (tile_for_capture.getColor() == color)
                {
                    Tile& first_captured_stone = (map.*ptr)(tile, 1);
                    Tile& second_captured_stone = (map.*ptr)(tile, 2);

                    map.removeStone(first_captured_stone);
                    map.removeStone(second_captured_stone);

                    if (captured == 8)
                        return true;//TODO : est-ce necessaire de faire le += 2 ici aussi ?

                    captured += 2;
                    map.addCaptured(color, 2);
                }
            }
            catch (const ExcOutOfBound& e) {
            }
        }
    }

    return false;
}

Referee::E_STATE Referee::checkLbreakables(Map &map)
{
    for (std::list<std::pair<Tile&, Map::E_DIR>>::iterator it = this->_breakables.begin();
            it != this->_breakables.end(); ++it)
    {
        if ((*it).first.getColor() == Stone::NONE)
        {
            (*it).first._breakable = false;
            this->_breakables.erase(it);
        }
        else if (isTileBreakable((*it).first, map) == false)
        {
            (*it).first._breakable = false;
            E_STATE ret = checkAlign(map[(*it).first.Y][(*it).first.X], map, true);
            if (ret != VALID)
                return ret;
            this->_breakables.erase(it);
        }
    }
    return VALID;
} //ToDo mettre dans meme if //ToDo implanter dans boucle //Todo new func with direction //Todo const?

/* ALIGNEMENT FUNCTIONS */
Referee::E_STATE Referee::checkAlign(Tile& t, Map& m, bool breakable) {
    for (int ori = Map::E_OR::NS; ori != Map::E_OR::MAX; ++ori)
    {
        Map::E_DIR d = Map::OR_TO_DIR[ori];
        if (t.getIntValue(t.getColor(), d) >= 5
                && (breakable == false || isAlignBreakable(t, m, d) == false))
            return this->winner(t.getColor());
    }
    return VALID;
}

bool Referee::isAlignBreakable(Tile &t, Map &m, Map::E_DIR dir)
{
    Tile&    next = t;
    int     count = 5; // TODO Why is this shit ?
    Map::E_OR ori = Map::E_OR::MAX;

    try {
        while (count > 0 && next.getColor() == t.getColor())
        {
            if ((ori = isTileBreakable(next, m)) != Map::E_OR::MAX)
                break;
            next = (m.*(m.go[dir]))(next, 1);
            count--;
        }
    }
    catch (const ExcOutOfBound& ex){
    }

    try {
        dir = Map::OP_DIR[dir];
        next = (m.*(m.go[dir]))(t, 1);
        while (count > 0 && next.getColor() == t.getColor())
        {
            if ((ori = isTileBreakable(next, m)) != Map::E_OR::MAX)
                break;
            next = (m.*(m.go[dir]))(next, 1);
            count--;
        }
    }
    catch (const ExcOutOfBound& ex){
    }

    if (count == 0)
        return false;
    return true;
}

Map::E_OR Referee::isTileBreakable(Tile &start, Map &m)
{
    for (int ori_int = Map::E_OR::NS; ori_int != Map::E_OR::MAX; ++ori_int)
    {
        try {
            Map::E_OR ori = static_cast<Map::E_OR>(ori_int);
            if (this->isOrBreakable(start, m, ori) == true)
                return ori;
        }
        catch (const ExcOutOfBound& ex){
            continue;
        }
    }
    return Map::E_OR::MAX;
}

bool Referee::isOrBreakable(Tile &start, Map &m, Map::E_OR ori)
{
        Tile& check = start;
        Map::E_DIR cdir = Map::OR_TO_DIR[ori];
        int end = 0;

        if (start.getIntValue(start.getColor(), cdir) == 2)
        {
            check = (m.*(m.go[cdir]))(check, 1);
            if (check.getColor() == start.getColor())
            {
                check = (m.*(m.go[cdir]))(check, 1);
                if (check.getColor() == Stone::NONE)
                    end++;
                check = (m.*(m.go[Map::OP_DIR[cdir]]))(check, 3);
                if (check.getColor() == Stone::NONE)
                    end++;
            }
            else
            {
                if (check.getColor() == Stone::NONE)
                    end++;
                check = (m.*(m.go[Map::OP_DIR[cdir]]))(check, 3);
                if (check.getColor() == Stone::NONE)
                    end++;
            }
            if (end == 1)
            {
                if (start._breakable == false)
                {
                    // Todo: Remove const of start
                    start._breakable = true;
                    this->_breakables.push_back(std::pair<Tile&, Map::E_DIR>(start, cdir));
                }
                return true;
            }
        }
    return false;
}

/* MEMBERS */
inline Referee::E_STATE Referee::winner(const Stone::E_COLOR color) const {
    if (color == Stone::BLACK)
        return END_BLACK;
    return END_WHITE;
}


/* OLD */

// bool Referee::parcoursOne(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
// {
//     Map::PTR ptr = map.go[first_dir];
//
//     if (checkDoubleThreeSecondPart(map, tile, color, first_dir))
//         return true;
//
//     Tile& second_tile = (map.*ptr)(tile, 2);
//     if (checkDoubleThreeSecondPart(map, second_tile, color, first_dir))
//         return true;
//
//     Tile& third_tile = (map.*ptr)(tile, 3);
//     if (checkDoubleThreeSecondPart(map, third_tile, color, first_dir))
//         return true;
//
//     return false;
// }

// bool Referee::parcoursTwo(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
// {
//     Map::PTR ptr = map.go[first_dir];
//
//     if (checkDoubleThreeSecondPart(map, tile, color, first_dir))
//         return true;
//
//     Tile& second_tile = (map.*ptr)(tile, 1);
//     if (checkDoubleThreeSecondPart(map, second_tile, color, first_dir))
//         return true;
//
//     Tile& third_tile = (map.*ptr)(tile, 3);
//     if (checkDoubleThreeSecondPart(map, third_tile, color, first_dir))
//         return true;
//
//     return false;
// }

// bool Referee::parcoursThree(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
// {
//     Map::PTR ptr = map.go[first_dir];
//
//     if (checkDoubleThreeSecondPart(map, tile, color, first_dir))
//         return true;
//
//     Tile& second_tile = (map.*ptr)(tile, 1);
//     if (checkDoubleThreeSecondPart(map, second_tile, color, first_dir))
//         return true;
//
//     Tile& third_tile = (map.*ptr)(tile, 2);
//     if (checkDoubleThreeSecondPart(map, third_tile, color, first_dir))
//         return true;
//
//     return false;
// }

/*bool Referee::extremOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, 4);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}
*/

/*bool Referee::extremTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, tile.getValue(color, dir) + 3);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, tile.getValue(color, Map::OP_DIR[dir]) + 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}
*/

/*bool Referee::extremThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, tile.getValue(color, dir) + 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, tile.getValue(color, Map::OP_DIR[dir]) + 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}
*/
