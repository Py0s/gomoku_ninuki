
#include "Stone.h"
#include "Referee.h"
#include "ExcOutOfBound.h"

const enum Stone::E_COLOR Referee::OP_COLOR[] = { Stone::WHITE, Stone::BLACK };

Referee::Referee() {

}

Referee::~Referee() {

}

Referee::E_STATE Referee::check(const Stone& s, Map& map, APlayer* player) {
    if (map[s.y()][s.x()].getColor() != Stone::E_COLOR::NONE)
        return INVALID;

    map.placeStone(s);

    // if RULE
    checkDoubleThree();

    checkCapture(map[s.y()][s.x()], map, player);

    E_STATE ret = checkAlign(map[s.y()][s.x()], map);

    // map.displayDebug();
    return ret;
}

void Referee::checkDoubleThree() const {

}

void Referee::checkCapture(Tile& tile, Map& map, APlayer* player) const {
    Stone::E_COLOR color = tile.getColor();

    for (int dir = 0; dir < 8; ++dir)
    {
        if (map[tile.Y][tile.X].getValue(Referee::OP_COLOR[color], dir) == 2)
        {
            try
            {
                Map::PTR ptr = map.go[dir];
                Tile& tile_for_capture = (map.*ptr)(tile, 3);

                if (tile_for_capture.getColor() == color)
                {
                    player->captureStones();

                    Tile& first_captured_stone = (map.*ptr)(tile, 1);
                    Tile& second_captured_stone = (map.*ptr)(tile, 2);

                    map.removeStone(first_captured_stone);
                    map.removeStone(second_captured_stone);
                }
            }
            catch (const ExcOutOfBound& e) {
            }
        }
    }
}

Referee::E_STATE Referee::checkAlign(Tile& t, Map& m) {
    for (int ori = Map::E_OR::NS; ori != Map::E_OR::MAX; ++ori)
    {
        Map::E_DIR d = Map::OR_TO_DIR[ori];
        if (t.getIntValue(t.getColor(), d) >= 5
                && isAlignBreakable(t, m, d) == false)
            return this->winner(t.getColor());
    }
    return VALID;
}

bool Referee::isAlignBreakable(const Tile &t, Map &m, Map::E_DIR dir)
{
    Tile    next = t;
    int     count = 5;
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

Map::E_OR Referee::isTileBreakable(const Tile &start, Map &m) const
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

bool Referee::isOrBreakable(const Tile &start, Map &m, Map::E_OR ori) const
{
        Tile check = start;
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
                return true;
        }
    return false;
}

inline Referee::E_STATE Referee::winner(const Stone::E_COLOR color) const {
    if (color == Stone::BLACK)
        return END_BLACK;
    return END_WHITE;
}
