#include <iostream>
#include "tetris.hpp"


int main()
{
    Kenton::Tetris game(15,20);
    game.start();
    std::cin.get();
    return 0;
}
