//
// Created by Ran Levy on 07/02/2021.
//

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Machine.h"
#include "PacMan.h"
#include "Ghost.h"

// ToDo - Make machine a member of Game
// Todo - Check memory leaks when quiting game



class Cell {

public:
    explicit Cell(int cellData);
    void draw(Machine &machine, int x0, int y0);
private:
    bool _upWall, _downWall, _rightWall, _leftWall;
};

class Game {
public:

    Game();
    int play(const std::string& gameFileName);
private:
    void initGameData(const std::string& gameFileName);
    void drawGameBoard(Machine &machine) const;

    int _numRows;
    int _numCols;
    std::vector<std::vector<std::unique_ptr<Cell>>> _board;
    int _score;
    PacMan _pacman;
    Ghost _ghosts[4];
};

