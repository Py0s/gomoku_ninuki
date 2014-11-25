#include "Referee.h"

Referee::Referee() {

}

Referee::~Referee() {

}

bool Referee::check(const Stone& s, Map& map) const {
    if (map.getMap()[s.y()][s.y()].getColor() != Stone::NONE)
        return false;

    map.placeStone(s);
    // if RULE
    checkDoubleThree();

    checkCapture();

    checkAlign();
    return true;
}

void Referee::checkDoubleThree() const {

}

void Referee::checkCapture() const {

}

void Referee::checkAlign() const {

}
