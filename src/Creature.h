//
// Created by Ran Levy on 10/02/2021.
//


#pragma once

#include <SDL.h>
#include <memory>
#include "Machine.h"

class Creature {
public:
    Creature();
    Creature(int currentRow, int currentCol, const std::string& imageFileName);
    void draw(Machine &machine) const;

private:
    int _currentRow;
    int _currentCol;
    float _xOffset;         // x offset of creature fro cell center
    float _yOffset;         // y offset of creature fro cell center
    std::unique_ptr<SDL_Surface>  _image;
};


