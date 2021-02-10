//
// Created by Ran Levy on 10/02/2021.
//

#pragma once

#include "Creature.h"

class Ghost: public Creature {
public:
    Ghost();
    Ghost(int currentRow, int currentCol, const std::string &imageFileName);

};


