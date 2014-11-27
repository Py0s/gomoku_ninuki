
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
    if (t.intervalue[t.color()][N] >= 5)
        return this->winner(t.color());  //This->_break == list des cassaables
    //if (t.intervalue[t.color()][W] >= 5
    // && is_breakable(E, t, m, this->_break)); This->_break == list des cassaables
    //if (t.intervalue[t.color()][NW] >= 5
    // && is_breakable(NW, t, m, this->_break)); This->_break == list des cassaables
    //if (t.intervalue[t.color()][NE] >= 5
    // && is_breakable(NE, t, m, this->_break)); This->_break == list des cassaables
    return VALID;
}

inline Referee::E_STATE Referee::winner(Stone::E_COLOR color) {
    if (color == Stone::BLACK)
        return END_BLACK;
    return END_WHITE;
}