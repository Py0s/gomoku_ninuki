#pragma once

#include "IPlayer.h"

class Human : public IPlayer
{
public:
    Human();
    ~Human();

    bool    plays();
};
