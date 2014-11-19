#include "Map.h"
#include "NCurses.h"
#include <iostream>
#include <sstream>

Map::Map() {
}

Map::~Map() {
}

// Getters
int Map::mapSizeX() {
    return this->_MAPSIZE_X;
}

int Map::mapSizeY() {
    return this->_MAPSIZE_Y;
}

char const * Map::displayMap() const {
    return (char const *)&this->_display_map;
}

void Map::debugMap()
{
    std::stringstream msg;
    for (int y = 0; y < this->_MAPSIZE_X; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            msg << "[" << y << ";" << x << "] : ";
            msg << "N[";
            for (int i = 0; i < 8; ++i)
            {
                msg << this->_map[y][x]._infos[Square::BLACK]._values[i] + '\0';
            }
/*            msg << "] | ";
            msg << "B [";
            for (int i = 0; i < 8; ++i)
            {
                msg << this->_map[y][x]._infos[Square::WHITE]._values[i] + '\0';
            }
            msg << "]\t";
*/        }
        msg << "\n";
    }
    NCurses::DebugPrint(msg.str());
}

// Setters
void Map::setDisplayMap(int y, int x, char c) {
    this->_display_map[y][x] = c;
}

bool Map::isBreakable(int y, int x, Square::Color me, Square::Color other)
{
    for(int dir = 0; dir <= 3; ++dir)
    {
      if (this->_map[y][x]._infos[me]._values[dir] == 2)
      {
          std::pair<int,int> vec = Square::directionToVector(static_cast<Square::Direction>(dir));
          std::pair<int,int> vec2 = Square::directionToVector(Square::opposedDirection(static_cast<Square::Direction>(dir)));
          Square::Color right = this->_map[y + vec.second][x + vec.first]._player;
          Square::Color left = this->_map[y + vec2.second][x + vec2.first]._player;
          Square::Color right2 = this->_map[y + vec.second * 2][x + vec.first * 2]._player;
          Square::Color left2 = this->_map[y + vec2.second * 2][x + vec2.first * 2]._player;

          if (right == other && left2 == Square::UNDEFINED)
          {
              if ((y + vec2.second * 2) < 0 || (x + vec2.first * 2) < 0)
                  return false;
              return true;
          }
          if (left == other && right2 == Square::UNDEFINED)
          {
              if ((y + vec.second * 2) < 0 || (x + vec.first * 2) < 0)
                  return false;
              return true;
          }
          if (right2 == other && left == Square::UNDEFINED)
          {
              if ((y + vec2.second) < 0 || (x + vec2.first) < 0)
                  return false;
              return true;
          }
          if (left2 == other && right == Square::UNDEFINED)
          {
              if ((y + vec.second) < 0 || (x + vec.first) < 0)
                  return false;
              return true;
          }
      }
    }
    return false;
}

bool Map::checkEnd(int y, int x, Square::Color color)
{
    for(int dir = 0; dir <= 7; ++dir)
    {
      if (this->_map[y][x]._infos[color]._values[dir] == 5)
      {
          int adver;
          if (color == Square::Color::BLACK)
              adver = Square::Color::WHITE;
          else if (color == Square::Color::WHITE) ///TODO T un connard
              adver = Square::Color::BLACK;
          std::pair<int,int> vec = Square::directionToVector(static_cast<Square::Direction>(dir));
          for (int i = 0; i <=4; ++i)
          {
              if (isBreakable(y, x, color, static_cast<Square::Color>(adver)) == true)
                  return false;
              y = y + vec.second;
              x = x + vec.first;
          }
          std::cout << "YOU WIN!!!!" << std::endl;
          return true;
      }
    }
    return false;
}

bool Map::checkBreak(int y, int x, Square::Color color)
{
    int adver;

    if (color == Square::Color::BLACK)
        adver = Square::Color::WHITE;
    else if (color == Square::Color::WHITE) ///TODO T un connard
        adver = Square::Color::BLACK;
    for(int dir = 0; dir <= 7; ++dir)
    {
        if (this->_map[y][x]._infos[adver]._values[dir] == 3)
        {
            std::pair<int,int> vec = Square::directionToVector(static_cast<Square::Direction>(dir));
            if (this->_map[y + vec.second * 3][x + vec.first * 3]._player == color)
            {
                std::cout << "You have taken two stones" << std::endl; //TODO
                this->_map[y + vec.second][x + vec.first]._player = Square::UNDEFINED;
                this->_map[y + vec.second * 2][x + vec.first * 2]._player = Square::UNDEFINED;

                updateMap(static_cast<Square::Color>(adver));

                //breakMap(y + vec.second, x + vec.first, static_cast<Square::Color>(adver));
                //breakMap(y + vec.second * 2, x + vec.first * 2, static_cast<Square::Color>(adver));

                this->_taken[color] += 2;
                if (this->_taken[color] > 9)
                {
                    std::cout << "YOU WIN!!!!" << std::endl;
                    return true;
                }
          }
      }
    }
    return true;
}

//on interdit de jouer sur l'autre ?
bool Map::checkDoubleThree(int y, int x, Square::Color color)
{
  //start preview
  _map[y][x]._player = color;
  updateMap(color);

  //do check
  bool isDoubleThree = doubleThreeRealCheck(y,x,color);

  //cancel preview
  _map[y][x]._player = Square::UNDEFINED;
  updateMap(color);

  return isDoubleThree;
}

bool Map::doubleThreeRealCheck(int y, int x, Square::Color color)
{
  //check if there is a three-config on these square
  Square::Direction firstDir = doubleThreeSquare(y,x,color);
  if (firstDir == Square::DIRECTION_COUNT)
    return false;

  //check if there is another three-config on the line of the first
 Square::Direction firstOpposedDir = Square::opposedDirection(firstDir);
 //check the two side of the line
 return (doubleThreeMidLine(y,x,color,firstDir) || doubleThreeMidLine(y,x,color,firstOpposedDir));
}

bool Map::doubleThreeMidLine(int y, int x, Square::Color color, Square::Direction dir)
{
  int tmp_y = y, tmp_x = x;
  while (_map[tmp_y][tmp_x]._player == color || getInterValue(tmp_y,tmp_x,color,dir) == 4)//>= 4 ??
  {
    goToNextCase(tmp_y,tmp_x,dir);
    if (coord_not_ok(tmp_y,tmp_x) || _map[tmp_y][tmp_x]._player == Square::opponentColor(color))
      return false;
    if (doubleThreeSquareExceptDir(tmp_y,tmp_x,color,dir) != Square::DIRECTION_COUNT)
      return true;
  }
  return false;
}

//return Square::DIRECTION_COUNT if no line match
Square::Direction Map::doubleThreeSquare(int y, int x, Square::Color color)
{
  for (int i = 0; i < 8; ++i)
  {
    Square::Direction dir = static_cast<Square::Direction>(i);
      // if a three-config is found return its direction
    if (doubleThreeLine(y,x,color,dir))
      return dir;
  }
  return Square::DIRECTION_COUNT;
}

//return Square::DIRECTION_COUNT if no line match
Square::Direction Map::doubleThreeSquareExceptDir(int y, int x, Square::Color color, Square::Direction exceptDir)
{
  Square::Direction exceptDir2 = Square::opposedDirection(exceptDir);
  for (int i = 0; i < 8; ++i)
  {
    Square::Direction dir = static_cast<Square::Direction>(i);
    if (dir != exceptDir && dir != exceptDir2)
    {
      // if a three-config is found return its direction
      if (doubleThreeLine(y,x,color,dir))
        return dir;
    }
  }
  return Square::DIRECTION_COUNT;
}

bool Map::doubleThreeLine(int y, int x, Square::Color color, Square::Direction dir)
{
  int tmp_y = y, tmp_x = x;
  if (!goToEndOfLine(tmp_y, tmp_x, color, dir) || _map[tmp_y][tmp_x]._player == Square::opponentColor(color))
    return false;
  if (getInterValue(tmp_y, tmp_x, color, dir) != 4)// >= 4 ??
    return false;
  Square::Direction opposedDir = Square::opposedDirection(dir);
  tmp_y = y;
  tmp_x = x;
  if (!goToEndOfLine(tmp_y, tmp_x, color, dir) || _map[tmp_y][tmp_x]._player == Square::opponentColor(color))
    return false;
  if (getInterValue(tmp_y, tmp_x, color, opposedDir) != 4)// >= 4 ??
    return false;
  return true;
}
/*// retourne false si on est sorti de la map
bool Map::goToEndOfThreeLine(int &y, int &x, Square::Color color, Square::Direction dir)
{
  while (_map[y][x]._player == color ||  && goToNextCase(y,x,dir));
  return coord_ok(y,x);
}
*/
bool Map::updateMap(Square::Color color)
{
  for (int y = 0; y < _MAPSIZE_Y; ++y)
  {
    for (int x = 0; x < _MAPSIZE_X; ++x)
    {
      updateSquare(y,x,color);
      updateInterValue(y,x,color);
    }
  }
  return true;
}

bool Map::updateSquare(int y, int x, Square::Color color)
{
  if (_map[y][x]._player == color)
  {
    return updateSquareWithStone(y,x,color);
  }
  return updateSquareWithoutStone(y,x,color);
}

bool Map::updateSquareWithStone(int y, int x, Square::Color color)
{
  for (int i = 0; i < 4; ++i)
  {
    Square::Direction dir = static_cast<Square::Direction>(i);
    Square::Direction opposedDir = Square::opposedDirection(dir);

    int tmp_y = y, tmp_x = x;
    goToEndOfLine(tmp_y,tmp_x,color,dir);

    char v = lineLength(tmp_y, tmp_x, color, opposedDir);
    setValue(y,x,color,dir,v);
    setValue(y,x,color,opposedDir,v);
  }
  return true;
}

bool Map::coord_ok(int y, int x)
{
  return (y >= 0 && x >= 0 && y < _MAPSIZE_Y && x < _MAPSIZE_X);
}
bool Map::coord_not_ok(int y, int x)
{
  return (!coord_ok(y, x));
}

// retourne false si on est sorti de la map
bool Map::goToNextCase(int &y, int &x, Square::Direction dir)
{
  std::pair<int,int> dirVect = Square::directionToVector(dir);
  y += dirVect.second;
  x += dirVect.first;  
  return coord_ok(y,x);
}

// retourne false si on est sorti de la map
bool Map::goToEndOfLine(int &y, int &x, Square::Color color, Square::Direction dir)
{
  while (_map[y][x]._player == color && goToNextCase(y,x,dir));
  return coord_ok(y,x);
}

bool Map::updateSquareWithoutStone(int y, int x, Square::Color color)
{
  for (int i = 0; i < 8; ++i)
  {
    Square::Direction dir = static_cast<Square::Direction>(i);
    char v = lineLength(y,x,color,dir) + 1;
    setValue(y,x,color,dir,v);
  }
  return true;
}

// compte a partir de la prochaine case
char Map::lineLength(int y, int x, Square::Color color, Square::Direction dir)
{
  char v = 0;
  goToNextCase(y,x,dir);
  if (coord_not_ok(y,x))
  {
    return v;
  }
  while (_map[y][x]._player == color)
  {
    v += 1;
    goToNextCase(y,x,dir);
    if (coord_not_ok(y,x))
      return v;
  }
  return v;
}

void Map::setValue(int y, int x, Square::Color color, Square::Direction dir, char value)
{
  _map[y][x]._infos[color]._values[dir] = value;
}
char Map::getValue(int y, int x, Square::Color color, Square::Direction dir)
{
  return _map[y][x]._infos[color]._values[dir];
}
//faire le % 4 ou pas pour + opti ?
void Map::setInterValue(int y, int x, Square::Color color, Square::Direction dir, char value)
{
  _map[y][x]._infos[color]._interValues[dir % 4] = value;
}
char Map::getInterValue(int y, int x, Square::Color color, Square::Direction dir)
{
  return _map[y][x]._infos[color]._interValues[dir % 4];
}
void Map::updateInterValue(int y, int x, Square::Color color)
{
  for (int i = 0; i < 4; ++i)
  {
    Square::Direction dir = static_cast<Square::Direction>(i);
    Square::Direction opposedDir = Square::opposedDirection(dir);
    if (_map[y][x]._player == color)
    {
      setInterValue(y,x,color,dir,getValue(y,x,color,dir));
    }
    else
    {
      char v = getValue(y,x,color,dir) + getValue(y,x,color,opposedDir) - 1;
      setInterValue(y,x,color,dir,v);
    }
  }
}
