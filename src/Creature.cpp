//
// Created by Ran Levy on 10/02/2021.
//

#include "Creature.h"
#include <string>
#include "Game.h"
#include <cmath>

Creature::Creature() : _currentRow(0),
                       _currentCol(0),
                       _xOffset(0.0),
                       _yOffset(0.0),
                       _image(nullptr),
                       _game(nullptr){}
Creature::Creature(Game *game, int currentRow, int currentCol, const std::string& imageFileName) : _currentRow(currentRow),
                                                                                       _currentCol(currentCol),
                                                                                       _xOffset(0.0),
                                                                                       _yOffset(0.0),
                                                                                       _game(game)
{
    _image.reset(SDL_LoadBMP(imageFileName.c_str()));
}

void Creature::draw(Machine &machine) const{
    machine.drawImage(_image.get(),
                      _currentCol * CELL_SIZE + BOARD_MARGIN + CELL_MARGIN + static_cast<int>(_xOffset * CELL_SIZE),
                      _currentRow * CELL_SIZE + BOARD_MARGIN + CELL_MARGIN + static_cast<int>(_yOffset * CELL_SIZE));
}

void Creature:: setNextCell() {
    switch (_direction) {
        case Up:
            _nextRow = _currentRow - 1;
            _nextCol = _currentCol;
            break;
        case Down:
            _nextRow = _currentRow + 1;
            _nextCol = _currentCol;
            break;
        case Right:
            _nextRow = _currentRow;
            _nextCol = _currentCol + 1;
            break;
        case Left:
            _nextRow = _currentRow;
            _nextCol = _currentCol - 1;
            break;

    }
}

void Creature::move() {
    switch (_direction) {
        case Up:
            _yOffset -= STEP_SIZE;
            break;
        case Down:
            _yOffset += STEP_SIZE;
            break;
        case Right:
            _xOffset += STEP_SIZE;
            break;
        case Left:
            _xOffset -= STEP_SIZE;
            break;

    }

}

bool eq(float x, int y) {
    return abs(x - y) < 1e-4;
}

bool Creature::atCellCenter() const {

    return ((eq(_xOffset, 0) && eq(_yOffset, 0)) ||
            (_direction == Up && eq(_yOffset, -1)) ||
            (_direction == Down && eq(_yOffset, 1)) ||
            (_direction == Right && eq(_xOffset, 1)) ||
            (_direction == Left && eq(_xOffset, -1)));
}

int Creature::getCurrentRow() const {
    return _currentRow;
}

int Creature::getCurrentCol() const {
    return _currentCol;
}



