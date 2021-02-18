//
// Created by Ran Levy on 07/02/2021.
//

#include <iostream>
#include "Machine.h"

Machine::Machine():
        _window(nullptr, SDL_DestroyWindow),
        _renderer(nullptr, SDL_DestroyRenderer),
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

    _renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_SOFTWARE));
    if (_renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer.get());

    return true;
}

Machine::UserCommand Machine::poll() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_q:
                    return Quit;
                case SDLK_p:
                    return Pause;
                case SDLK_r:
                    return Resume;
                case SDLK_UP:
                    return MoveUp;
                case SDLK_DOWN:
                    return MoveDown;
                case SDLK_RIGHT:
                    return MoveRight;
                case SDLK_LEFT:
                    return MoveLeft;
            }
        }
    }
    return NoCommand;
}

void Machine::drawLine(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
//    SDL_RenderPresent(_renderer.get());
}

void Machine::drawRect(int x1, int y1, int x2, int y2) {
    SDL_Rect rect{
        x1, y1, x2, y2
    };
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(_renderer.get(), &rect);
//    SDL_RenderPresent(_renderer.get());
}

void Machine::drawImage(SDL_Surface *image, int x, int y){
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer.get(), image);
    SDL_Rect rect {
        x, y, image->w, image->h
    };
    SDL_RenderCopy(_renderer.get(), texture, nullptr, &rect);
//    SDL_RenderPresent(_renderer.get());
}

void Machine::render() {
    SDL_RenderPresent(_renderer.get());

}


