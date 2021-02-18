//
// Created by Ran Levy on 10/02/2021.
//

#pragma once

#include "Creature.h"

class Game;

class Ghost: public Creature {
public:
    Ghost();
    Ghost(Game *game, int currentRow, int currentCol, const std::string &imageFileName);
    void move();

private:
    void selectDirection();
};


