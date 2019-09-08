#include <iostream>
#include "tetris.h"

int main()
{
    Kenton::Tetris game(15,20);
    std::cout << "Press enter to start.";
    std::cin.get();
    system("cls");
    game.start();
    std::cin.get();
    return 0;
}
