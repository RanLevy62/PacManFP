//
// Created by Ran Levy on 07/02/2021.
//

#include "Game.h"
#include "Machine.h"
#include "graphic_constants.h"
#include <fstream>
#include <iostream>
#include <thread>

Game::Game():
    _numCols(0),
    _numRows(0),
    _board{},
    _score(0)
    {
}

/*
 initGameData - reads data from game data file, and use it to init Game Data

 game data file format
 ---------------------
 The file is a text file.
 Data items are separated by white spaces.
 Data is -
 1. Number of rows
 2. Number of columns
 3. Number of Rows * Number of columns of HEX numbers representing  cell data
    (starting from the leftmost cell in the top row, going thru top row, then moving left to right on the second row etc.)
    each number is a binary  representation of cell walls:
    bit 0 - top wall (value of "1" - there is a wall)
    bit 1 - right wall
    bit 2 - bottom wall
    bit 3 - left wall
 */
void Game::initGameData(const std::string& gameFileName) {
    _board.clear();
    std::ifstream gameFile(gameFileName);

    // Init game board
    gameFile >> _numRows >> _numCols;
    std::cout << "cols " << _numCols << "  rows " << _numRows << std::endl;

    for (int row = 0 ; row < _numRows ; row++) {
        std::vector<std::unique_ptr<Cell>> newRow;
        _board.emplace_back(std::move(newRow));
        for (int col = 0 ; col < _numCols ; col++) {
            int cellData;
            gameFile >> std::hex >> cellData;
            std::unique_ptr<Cell> c = std::make_unique<Cell>(cellData);
            _board[row].emplace_back(std::move(c));
        }
    }

    // Init Pacman and ghosts
    int pacmanRow, pacmanCol;
    std::string pacmanImageFileName;
    gameFile >> pacmanRow >> pacmanCol >> pacmanImageFileName;
    _pacman = PacMan(pacmanRow, pacmanCol, pacmanImageFileName);

    SDL_Surface *t = SDL_LoadBMP(pacmanImageFileName.c_str());
    std::cout  << SDL_GetError() << std::endl;

    int ghostRow, ghostCol;
    std::string ghostImageFileName;
    for (auto & _ghost : _ghosts) {
        gameFile >> ghostRow >> ghostCol >> ghostImageFileName;
        _ghost = Ghost(ghostRow, ghostCol, ghostImageFileName);
    }


}

int Game::play(const std::string &gameFileName) {
    initGameData(gameFileName);

    const int SCREEN_WIDTH = 1100;
    const int SCREEN_HEIGHT = 1100;

    Machine machine;
    if (!machine.Init(SCREEN_HEIGHT, SCREEN_WIDTH)) {
        std::cout << "Couldn't init machine. Aborting...\n";
        return(-1);
    }

    drawGameBoard(machine);

    bool quit = false;
    bool paused = false;
    int i = 0;
    while (!quit) {
        Machine::UserCommand command = machine.poll();

        switch (command) {
            case Machine::Quit :
                quit = true;
                break;
            case Machine::Pause:
                paused = true;
                break;
            case Machine::Resume:
                paused = false;
                break;
            default:
                break;
        }
    }
    return _score;
}

void Game::drawGameBoard(Machine &machine) const {
    for (int row = 0 ; row < _numRows ; row++) {
        for (int col = 0 ; col < _numCols ; col++) {
            _board[row][col].get()->draw(machine, col * CELL_SIZE + 5, row * CELL_SIZE + 5);
        }
    }

    _pacman.Creature::draw(machine);
    for (int i = 0 ; i < 4 ; i++) {
        _ghosts[i].draw(machine);
    }
}


Cell::Cell(int cellData):
    _upWall((cellData & 0x01) == 0x01),
    _rightWall((cellData & 0x02) == 0x02),
    _downWall((cellData & 0x04) == 0x04),
    _leftWall((cellData & 0x08) == 0x08)
{
}

void Cell::draw(Machine &machine, int x0, int y0) {
    if (_upWall) machine.drawLine(x0, y0, x0 + CELL_SIZE, y0);
    if (_downWall) machine.drawLine(x0, y0 + CELL_SIZE, x0 + CELL_SIZE, y0 + CELL_SIZE);
    if (_rightWall) machine.drawLine(x0 + CELL_SIZE, y0, x0 + CELL_SIZE, y0 + CELL_SIZE);
    if (_leftWall) machine.drawLine(x0, y0, x0 , y0 + CELL_SIZE);

}
