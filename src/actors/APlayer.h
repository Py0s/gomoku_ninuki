#pragma once
#include "Stone.h"

class APlayer
{
  public:
    virtual ~APlayer() {};


    //Members
    virtual Stone   plays() = 0;
    virtual void    setColor(Stone::E_COLOR color) {
        this->_color = color;
    };
    virtual void    captureStones(){
        this->_capturedStones += 2;
    }
    
  protected:
    APlayer(): _color(Stone::E_COLOR::NONE) { };
    APlayer(Stone::E_COLOR color): _color(color), _capturedStones(0) { };
    
    Stone::E_COLOR _color;
    char _capturedStones;
};
