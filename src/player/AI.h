#pragma once

#include "IPlayer.h"
#include "Square.h"

class AI : public IPlayer
{
public:
    AI(Square::Color color = Square::WHITE);
    ~AI();

    bool    play();
};
