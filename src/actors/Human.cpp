#include "Human.h"

Human::Human(const Cursor& curs, Stone::E_COLOR color)
    : APlayer(color, APlayer::HUMAN), _curs(&curs) {
}

Human::~Human() {

}

//Members
Stone Human::plays() {
    return Stone(_curs->Y, _curs->X, _color);
}