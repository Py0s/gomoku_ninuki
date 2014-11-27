#pragma once

#include "APlayer.h"
#include "Cursor.h"

class Human : public APlayer
{
    public:
      Human(const Cursor& curs, Stone::E_COLOR color);
      virtual ~Human();
      
      virtual Stone plays();

    private:
      Cursor const * _curs;
};