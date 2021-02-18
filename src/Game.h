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


class Cell {

public:
    explicit Cell(int cellData);
    void draw(Machine &machine, int row, int col) const;
    bool hasDownWall() const;
    bool hasRightWall() const;
    bool hasLeftWall() const;
    bool hasUpWall() const;
private:
    bool _upWall, _downWall, _rightWall, _leftWall;
public:

};

class Game {
public:

    Game();
    int play(const std::string& gameFileName);
    bool directionValid(int row, int col, Direction dir);

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

