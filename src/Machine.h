//
// Created by Ran Levy on 07/02/2021.
//

#pragma once

#include <memory>
#include <SDL.h>

class Machine {

public:
    enum UserCommand {
        NoCommand,
        Quit,
        Pause,
        Resume,
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight
    };

    Machine();
    ~Machine();
    bool Init(int screenHeight, int screenWidth);
    UserCommand poll();

    void drawLine(int x1, int y1, int x2, int y2);
    void drawImage(SDL_Surface *image, int x, int y) ;
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
    std::unique_ptr<SDL_Renderer , decltype(&SDL_DestroyRenderer)> _renderer;
    int _screenHeight, _screenWidth;

};


