#include "Human.h"

Human::Human(const Cursor& curs, Stone::E_COLOR color): IPlayer(color), _curs(&curs) {
}

Human::~Human() {

}

//Members
Stone Human::plays() {
    return Stone(this->_curs->Y, this->_curs->X, this->_color);
}