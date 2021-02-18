//
// Created by Ran Levy on 10/02/2021.
//

#pragma once

#include "Creature.h"


class PacMan: public Creature {
public:
    PacMan();
    PacMan(Game *game, int currentRow, int currentCol, const std::string &imageFileName);
    void move();

private:
    Direction  _requestedDir;
public:
    void setRequestedDir(Direction requestedDir);

private:
    bool _blocked;
};


