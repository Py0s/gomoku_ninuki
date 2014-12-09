#include "Human.h"

Human::Human(const Cursor& curs, Stone::E_COLOR color)
    : APlayer(color, APlayer::HUMAN), _curs(&curs) {
}

Human::~Human() {

}

//Members
Stone Human::plays() {
    return Stone(this->_curs->Y, this->_curs->X, this->_color);
}