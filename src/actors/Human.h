#pragma once

#include "IPlayer.h"
#include "Cursor.h"

class Human : public IPlayer
{
    public:
      Human(const Cursor& curs, Stone::E_COLOR color);
      virtual ~Human();
      
      virtual Stone plays();

    private:
      Cursor const * _curs;
};