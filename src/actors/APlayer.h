#pragma once
#include "Stone.h"

class APlayer
{
  public:
    enum TYPE { HUMAN, AI };

    virtual ~APlayer() {};


    //Members
    virtual Stone   plays() = 0;
    virtual void    setColor(Stone::E_COLOR color) {
        this->_color = color;
    };

    //Getters
    virtual char& getCaptured() { return _captured; }
    virtual TYPE const& getType() const { return _type; }
    virtual const Stone::E_COLOR getColor() const { return _color; }
    
  protected:
//    APlayer(): _color(Stone::E_COLOR::NONE) { };
    APlayer();
    APlayer(Stone::E_COLOR color, TYPE type): _color(color), _captured(0), _type(type) { };
    
    Stone::E_COLOR _color;
    char    _captured;
    TYPE    _type;
};
