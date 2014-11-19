#include "Game.h"
#include "Exceptions.h"
#include <iostream>

int main(int ac, char * av[]) {
    try
    {
        if (ac == 1) {
            Game current(true);
            current.start();
        }
        else {
            Game current(false);
            current.start();
        }
    }
    catch (Exceptions& ex)
    {
        std::cout << ex.what() << std::endl;
        return ex.errNo();
    }
    return 0;
}
