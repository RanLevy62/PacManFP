//
// Created by Ran Levy on 10/02/2021.
//

#include "Creature.h"
#include "graphic_constants.h"
#include <string>

Creature::Creature() : _currentRow(0),
                       _currentCol(0),
                       _xOffset(0.0),
                       _yOffset(0.0),
                       _image(nullptr){}
Creature::Creature(int currentRow, int currentCol, const std::string& imageFileName) : _currentRow(currentRow),
                                                     _currentCol(currentCol),
                                                     _xOffset(0.0),
                                                     _yOffset(0.0) {
    _image.reset(SDL_LoadBMP(imageFileName.c_str()));
}

// Todo - 100 = Cell size
void Creature::draw(Machine &machine) const{
    machine.drawImage(_image.get(), _currentCol * CELL_SIZE + MARGIN , _currentRow * CELL_SIZE + MARGIN);
}

