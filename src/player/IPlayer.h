#pragma once

class IPlayer
{
public:
    virtual ~IPlayer();

    virtual bool    play() = 0;
};
