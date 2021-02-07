#include <iostream>
#include "Machine.h"

int main() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    Machine machine;
    machine.Init(SCREEN_HEIGHT, SCREEN_WIDTH);

    bool quit = false;
    bool paused = false;
    while (!quit) {
        Game::UserCommand command = machine.poll();

        switch (command) {
            case Game::Quit :
                quit = true;
                break;
            case Game::Pause:
                paused = true;
                break;
            case Game::Resume:
                paused = false;
                break;
            default:
                break;
        }
    }
    return 0;
}
