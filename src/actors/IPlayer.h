#pragma once

class IPlayer
{
public:
    virtual ~IPlayer();

    virtual bool    plays() = 0;
};
