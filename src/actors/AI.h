#pragma once

#include "APlayer.h"

class AI : public APlayer
{
public:
    AI();
    ~AI();

    virtual Stone    plays();
};
