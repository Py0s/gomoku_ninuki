
#include "Stone.h"

#include "Referee.h"

Referee::Referee() {

}

Referee::~Referee() {

}

Referee::E_STATE Referee::check(const Stone& s, Map& map) const {
    if (map[s.y()][s.x()].getColor() != Stone::E_COLOR::NONE)
        return INVALID;

    map.placeStone(s);

    // map.displayDebug();

    // if RULE
    checkDoubleThree();

    checkCapture(map.getMap()[s.y()][s.x()], map);

    E_STATE ret = checkAlign(map[s.y()][s.x()], map);
    return ret;
}

void Referee::checkDoubleThree() const {

}

void Referee::checkCapture(Tile& , Map& ) const {

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