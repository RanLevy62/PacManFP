//
// Created by Ran Levy on 07/02/2021.
//

#pragma once

#include <memory>
#include <SDL.h>
#include "Game.h"

class Machine {

public:
    Machine();
    ~Machine();
    bool Init(int screenHeight, int screenWidth);
    Game::UserCommand poll();

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
    SDL_Surface* _screenSurface;
    int _screenHeight, _screenWidth;

};


