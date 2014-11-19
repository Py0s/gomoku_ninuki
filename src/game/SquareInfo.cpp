#include "SquareInfo.h"

SquareInfo::SquareInfo()
{
    int i;
    for (i = 0; i < 9; i++)
    {
        this->_values[i] = 1;
    }

    for (i = 0; i < 5; i++)
    {
        this->_interValues[i] = 1;
    }
}

SquareInfo::~SquareInfo()
{

}
