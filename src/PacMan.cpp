//
// Created by Ran Levy on 10/02/2021.
//

#include <string>
#include "PacMan.h"
#include "Game.h"

PacMan::PacMan() : Creature() {}

PacMan::PacMan(Game *game, int currentRow, int currentCol, const std::string &imageFileName) :
        Creature(game, currentRow, currentCol, imageFileName),
        _blocked(false),
        _requestedDir(Right){
    _direction = _requestedDir;
    setNextCell();

}

void PacMan::move() {
    if (!_blocked) {
        Creature::move();
    }
    if (Creature::atCellCenter()) {
        _direction = _requestedDir;
        _currentRow = _nextRow;
        _currentCol = _nextCol;
        _xOffset =0 ;
        _yOffset = 0;
        if (_game->directionValid(_currentRow, _currentCol, _direction)) {
            setNextCell();
            _blocked = false;
        } else {
            _blocked = true;
        }
    }
}

void PacMan::setRequestedDir(Direction requestedDir) {
    _requestedDir = requestedDir;
}

