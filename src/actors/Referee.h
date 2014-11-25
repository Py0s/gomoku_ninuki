#pragma once

#include "Stone.h"
#include "Map.h"

class Referee
{
public:
    Referee();
    ~Referee();

    bool check(const Stone& s, Map& map) const;
    void checkDoubleThree() const;
    void checkCapture() const;
    void checkAlign() const;
    
private:
};
