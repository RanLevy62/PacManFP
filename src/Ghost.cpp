//
// Created by Ran Levy on 10/02/2021.
//

#include "Ghost.h"

Ghost::Ghost() : Creature() {}
Ghost::Ghost(int currentRow, int currentCol, const std::string &imageFileName) :
        Creature(currentRow, currentCol, imageFileName) {}
