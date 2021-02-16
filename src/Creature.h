//
// Created by Ran Levy on 10/02/2021.
//


#pragma once

#include <SDL.h>
#include <memory>
#include "Machine.h"
#include "GameConstants.h"

class Game;

class Creature {
public:
    Creature();
    Creature(Game *game, int currentRow, int currentCol, const std::string& imageFileName);
    void draw(Machine &machine) const;
    virtual Direction requestedDirection() = 0;
    void move();
    bool atCellCenter() const;
    void setNextCell();
    int getCurrentRow() const;
    int getCurrentCol() const;
    int getNextRow() const;
    int getNextCol() const;

protected:
    int _currentRow;
    int _currentCol;
    float _xOffset;         // x offset of creature from cell center
    float _yOffset;         // y offset of creature from cell center
    std::unique_ptr<SDL_Surface>  _image;
    Game *_game;
    int _nextRow;
    int _nextCol;
    Direction _direction;

};


