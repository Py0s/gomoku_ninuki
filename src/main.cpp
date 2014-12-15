#include "Game.h"
#include "Exceptions.h"
#include <iostream>

int main(int argc, char * argv[]) {
    try
    {
        Game current;
        current.mainLoop();
    }
    catch (Exceptions& ex)
    {
        std::cout << ex.what() << std::endl;
        return ex.errNo();
    }
    return 0;
}
