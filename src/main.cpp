#include <iostream>
#include "Game.h"
#include <thread>

void printMainMenu() {
    std::cout << "Main Menu\n";
    std::cout << "0 - quit\n";
    std::cout << "1 - play easy\n";
    std::cout << "2 - play hard\n";
}

int main() {
    Game game;

    bool quit = false;
    int command;
    int gameResult;

    while (!quit) {
        printMainMenu();
        gameResult = 0;
        std::cin  >> command;
        switch (command) {
            case 0:
                quit = true;
                break;
            case 1:
                gameResult = game.play("../data/game1");
                break;
            case 2:
                gameResult = game.play("../data/game2");
                break;
            default:
                break;
        }
        if (gameResult < 0) {
            std::cout << "Game error. Aborting...\n";
            exit(-1);
        } else {
            std::cout  << "Your score is " << gameResult << " points." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
