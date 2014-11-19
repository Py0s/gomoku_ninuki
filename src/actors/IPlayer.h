#pragma once
#include "Stone.h"

class IPlayer
{
  public:
    virtual ~IPlayer() {};


    //Members
    virtual Stone    plays() = 0;
    virtual void    setColor(Stone::E_COLOR color) {
        this->_color = color;
    };
    
  protected:
    IPlayer(): _color(Stone::E_COLOR::NONE) { };
    IPlayer(Stone::E_COLOR color): _color(color) { };
    
    Stone::E_COLOR _color;
};
