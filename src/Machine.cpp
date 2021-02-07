//
// Created by Ran Levy on 07/02/2021.
//

#include <iostream>
#include "Machine.h"

Machine::Machine():
        _window(nullptr, SDL_DestroyWindow),
        _screenSurface(nullptr),
        _screenHeight(0),
        _screenWidth(0)
{
}

Machine::~Machine() {
    SDL_Quit();
}

bool Machine::Init(int screenHeight, int screenWidth) {
    _screenHeight = screenHeight;
    _screenWidth = screenWidth;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    _window.reset(SDL_CreateWindow("PacMan Final Project",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   _screenWidth,
                                   _screenHeight,
                                   SDL_WINDOW_SHOWN));

    if (_window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }


//    int imgFlags = IMG_INIT_JPG;
//    if ( !IMG_Init(imgFlags)) {
//        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
//        return false;
//    }

    _screenSurface = SDL_GetWindowSurface(_window.get());
    SDL_FillRect( _screenSurface, nullptr, SDL_MapRGB( _screenSurface->format, 0x0, 0x0, 0xFF ) );

    //Update the surface
    SDL_UpdateWindowSurface( _window.get() );

    return true;
}

Game::UserCommand Machine::poll() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_q:
                    return Game::Quit;
                case SDLK_p:
                    return Game::Pause;
                case SDLK_r:
                    return Game::Resume;
            }
        }
    }
    return Game::NoCommand;
}