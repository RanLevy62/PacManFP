//
// Created by Ran Levy on 10/02/2021.
//

#include "Ghost.h"
#include "Game.h"
Ghost::Ghost() : Creature() {}

Ghost::Ghost(Game *game, int currentRow, int currentCol, const std::string &imageFileName) :
        Creature(game, currentRow, currentCol, imageFileName) {
    selectDirection();
}

// Ghosts select direction randomly. They just have to make sure this is a valid direction
void Ghost::selectDirection() {
    bool selected = false;
    while (!selected) {
        Direction requested = static_cast<Direction>(rand() % 4);
        if(_game->directionValid(_currentRow, _currentCol, requested)) {
            _direction = requested;
            setNextCell();
            selected = true;
        }
    }
}

void Ghost::move() {
    Creature::move();
    if(Creature::atCellCenter()) {
        _currentRow = _nextRow;
        _currentCol = _nextCol;
        _xOffset =0 ;
        _yOffset = 0;
        if (_game->directionValid(_currentRow, _currentCol, _direction)) {
            setNextCell();
        } else {
            selectDirection();
        }

    }
}
