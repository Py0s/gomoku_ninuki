#include "Square.h"

Square::Square()
{
    this->_player = UNDEFINED;
}

Square::~Square()
{
}

std::pair<int,int> Square::directionToVector(Square::Direction const& dir)
{
    switch (dir)
    {
        case UP_LEFT: return std::pair<int,int>(-1,-1);
        case UP: return std::pair<int,int>(0,-1);
        case UP_RIGHT: return std::pair<int,int>(1,-1);
        case RIGHT: return std::pair<int,int>(1,0);
        case DOWN_RIGHT: return std::pair<int,int>(1,1);
        case DOWN: return std::pair<int,int>(0,1);
        case DOWN_LEFT: return std::pair<int,int>(-1,1);
        case LEFT: return std::pair<int,int>(-1,0);
        default:
            break;
    }
    return std::pair<int,int>(-2,-2);//??
}
/*std::pair<int,int> const& nextPosInDirection(Direction const& dir, std::pair<int,int>& pos)
{
    std::pair<int,int> dirVect = directionToVector(dir);
    pos += dirVect;
    return pos;
}
*/
Square::Direction Square::vectorToDirection(std::pair<int,int> const& coord)
{
    //TODO
    return Square::DIRECTION_COUNT;
}

Square::Color Square::opponentColor(Square::Color color)
{
  if (color == Square::BLACK)
    return Square::WHITE;
  else
    return Square::BLACK;
}
