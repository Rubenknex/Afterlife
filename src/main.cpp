#include <iostream>

#include "Game.h"

int main()
{
    Game game;

    try
    {
        game.run();
    }
    catch(const char* error)
    {
        std::cout << error << std::endl;
    }

    return 0;
}
