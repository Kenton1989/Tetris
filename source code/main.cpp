#include <iostream>
#include "tetris.h"

int main()
{
    std::cout << "Press enter to start.";
    std::cin.get();
    system("cls");
    Kenton::Tetris game(15,20);
    game.start();
    std::cin.get();
    return 0;
}
