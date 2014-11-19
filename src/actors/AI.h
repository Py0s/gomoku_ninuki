#pragma once

#include "IPlayer.h"

class AI : public IPlayer
{
public:
    AI();
    ~AI();

    virtual Stone    plays();
};
