
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

    if (t.getIntValue(t.getColor(), Map::N) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list(t) else ...
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::W) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list() else ...
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::NW) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list() else ...
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::NE) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list() else ...
        return this->winner(t.getColor());
    return VALID;
}

inline Referee::E_STATE Referee::winner(const Stone::E_COLOR color) const {
    if (color == Stone::BLACK)
        return END_BLACK;
    return END_WHITE;
}