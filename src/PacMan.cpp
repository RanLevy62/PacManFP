//
// Created by Ran Levy on 10/02/2021.
//

#include <string>
#include "PacMan.h"

PacMan::PacMan() : Creature() {}

PacMan::PacMan(int currentRow, int currentCol, const std::string &imageFileName) :
        Creature(currentRow, currentCol, imageFileName) {

}


