#pragma once

#include "IPlayer.h"
#include "Square.h"

class Player : public IPlayer
{
public:
    Player(Square::Color color = Square::WHITE);
    ~Player();

    bool    play();
};
