//
// Created by Ran Levy on 10/02/2021.
//
#include "Creature.h"

#pragma once

class PacMan: public Creature {
public:
    PacMan();
    PacMan(int currentRow, int currentCol, const std::string &imageFileName);

};


