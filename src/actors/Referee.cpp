#include "Referee.h"

Referee::Referee() {

}

Referee::~Referee() {

}

bool Referee::check(const Stone& s, Map& map) const {
    if (map.getMap()[s.y()][s.x()].getColor() != Stone::E_COLOR::NONE)
        return false;

    map.placeStone(s);

    // map.displayDebug();

    // if RULE
    checkDoubleThree();

    checkCapture(map.getMap()[s.y()][s.x()], map);

    checkAlign();
    return true;
}

void Referee::checkDoubleThree() const {

}

void Referee::checkCapture(Tile& , Map& ) const {

}

void Referee::checkAlign() const {
// if RULE
}
