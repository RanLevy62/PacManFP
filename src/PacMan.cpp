//
// Created by Ran Levy on 10/02/2021.
//

#include <string>
#include "PacMan.h"

PacMan::PacMan() : Creature() {}

PacMan::PacMan(Game *game, int currentRow, int currentCol, const std::string &imageFileName) :
        Creature(game, currentRow, currentCol, imageFileName) {

}

Direction PacMan::requestedDirection() {
    return Left;
}


