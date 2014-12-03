
#include "Stone.h"
#include "Referee.h"
#include "ExcOutOfBound.h"

const enum Stone::E_COLOR Referee::OP_COLOR[] = { Stone::WHITE, Stone::BLACK };

Referee::Referee() {

}

Referee::~Referee() {

}

Referee::E_STATE Referee::check(const Stone& s, Map& map, APlayer* player) const {
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

Referee::E_STATE Referee::checkAlign(Tile& t, Map& m) const {
    // TODO: need to make a function from E_Dir to direction

    if (t.getIntValue(t.getColor(), Map::N) >= 5
            && isAlignBreakable(t, m, Map::N) == false)
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::W) >= 5
            && isAlignBreakable(t, m, Map::W) == false)
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::NW) >= 5
            && isAlignBreakable(t, m, Map::NW) == false)
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::NE) >= 5
            && isAlignBreakable(t, m, Map::NE) == false)
        return this->winner(t.getColor());
    return VALID;
}

bool Referee::isAlignBreakable(const Tile &t, Map &m, Map::E_DIR dir) const
{
    Tile    next = t;
    int     count = 5;

    while (next.getColor() == t.getColor() && count > 0)
    {
        if (isBreakable(next, m) == true)
            break;
        next = (m.*(m.go[dir]))(next, 1);
        count--;
    }
    dir = Map::OP_DIR[dir];
    next = (m.*(m.go[dir]))(t, 1);
    while (next.getColor() == t.getColor() && count > 0)
    {
        if (isBreakable(next, m) == true)
            break;
        next = (m.*(m.go[dir]))(next, 1);
        count--;
    }
    if (count == 0)
        return false;
    return true;
}

bool Referee::isBreakable(const Tile &start, Map &m) const
{
    for (int ori = Map::E_OR::NS; ori != Map::E_OR::MAX; ++ori)
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
    }
    return false;
}

inline Referee::E_STATE Referee::winner(const Stone::E_COLOR color) const {
    if (color == Stone::BLACK)
        return END_BLACK;
    return END_WHITE;
}
