//
// Created by Ran Levy on 07/02/2021.
//

#include "Game.h"
#include "Machine.h"
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
 4. PacMan initial data - row number, column number and image file name
 5. four lines, containing Ghosts initial data (same format as PacMan)
 */
void Game::initGameData(const std::string& gameFileName) {
    _board.clear();
    std::ifstream gameFile(gameFileName);

    // Init game board
    gameFile >> _numRows >> _numCols;

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
    _pacman = PacMan(this, pacmanRow, pacmanCol, pacmanImageFileName);

    int ghostRow, ghostCol;
    std::string ghostImageFileName;
    for (auto & _ghost : _ghosts) {
        gameFile >> ghostRow >> ghostCol >> ghostImageFileName;
        _ghost = Ghost(this, ghostRow, ghostCol, ghostImageFileName);
    }


}

int Game::play(const std::string &gameFileName) {
    initGameData(gameFileName);

    const int SCREEN_WIDTH = (_numCols + 1) * CELL_SIZE ;
    const int SCREEN_HEIGHT = (_numRows + 1) * CELL_SIZE;

    Machine machine;
    if (!machine.Init(SCREEN_HEIGHT, SCREEN_WIDTH)) {
        std::cout << "Couldn't init machine. Aborting...\n";
        return(-1);
    }

    drawGameBoard(machine);


    // Game Loop
    bool quit = false;
    bool paused = false;
    bool gameOver = false;
    auto gameStartTime = std::chrono::system_clock::now();
    while (!quit && !gameOver) {

        auto gameLoopStopTime = std::chrono::system_clock::now() + std::chrono::milliseconds(GAME_LOOP_INTERVAL_MS);

        // handle input
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
            case Machine::MoveUp:
                _pacman.setRequestedDir(Up);
                break;
            case Machine::MoveDown:
                _pacman.setRequestedDir(Down);
                break;
            case Machine::MoveRight:
                _pacman.setRequestedDir(Right);
                break;
            case Machine::MoveLeft:
                _pacman.setRequestedDir(Left);
                break;
            default:
                break;
        }

        // before move - delete creatures
        if (!paused) {
            for (auto & _ghost : _ghosts) {
                int row1 = _ghost.getCurrentRow();
                int col1 = _ghost.getCurrentCol();
                _board[row1][col1].get()->draw(machine, row1, col1);

            }
            int row = _pacman.getCurrentRow();
            int col = _pacman.getCurrentCol();
            _board[row][col].get()->draw(machine, row, col);
        }


        // update game state
        if (!paused) {
            for (auto & ghost : _ghosts) {
                ghost.move();
            }
            _pacman.move();

            // test if PacMan was caught
            for (auto & ghost : _ghosts) {
                if ((ghost.getCurrentCol() == _pacman.getCurrentCol()) && (ghost.getCurrentRow() == _pacman.getCurrentRow())) {
                    gameOver = true;
                    _score = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - gameStartTime).count();
                    std::cout << "***** Game Over *******\n";
                }
            }
        }

        // render
        if (!paused) {
            for (auto & _ghost : _ghosts) {
                _ghost.draw(machine);
            }
            _pacman.draw(machine);
        }

        machine.render();
        // sync game loop time

        std::this_thread::sleep_until(gameLoopStopTime);
    }

    return _score;
}

void Game::drawGameBoard(Machine &machine) const {
    for (int row = 0 ; row < _numRows ; row++) {
        for (int col = 0 ; col < _numCols ; col++) {
            _board[row][col].get()->draw(machine, row, col);
        }
    }

    _pacman.Creature::draw(machine);
    for (const auto & _ghost : _ghosts) {
        _ghost.draw(machine);
    }

    machine.render();
}

bool Game::directionValid(int row, int col, Direction dir) {
    return (dir == Up  &&  !_board[row][col].get()->hasUpWall()) ||
           (dir == Down  &&  !_board[row][col].get()->hasDownWall()) ||
           (dir == Right  &&  !_board[row][col].get()->hasRightWall()) ||
           (dir == Left  &&  !_board[row][col].get()->hasLeftWall()) ;
}


Cell::Cell(int cellData):
    _upWall((cellData & 0x01) == 0x01),
    _rightWall((cellData & 0x02) == 0x02),
    _downWall((cellData & 0x04) == 0x04),
    _leftWall((cellData & 0x08) == 0x08)
{
}

void Cell::draw(Machine &machine, int row, int col) const {
    int x0 = col * CELL_SIZE + BOARD_MARGIN;
    int y0 = row * CELL_SIZE + BOARD_MARGIN;
    machine.drawRect(x0, y0, CELL_SIZE, CELL_SIZE);
    if (_upWall) machine.drawLine(x0, y0, x0 + CELL_SIZE - 1, y0);
    if (_downWall) machine.drawLine(x0, y0 + CELL_SIZE - 1, x0 + CELL_SIZE - 1, y0 + CELL_SIZE - 1);
    if (_rightWall) machine.drawLine(x0 + CELL_SIZE - 1, y0, x0 + CELL_SIZE - 1, y0 + CELL_SIZE - 1);
    if (_leftWall) machine.drawLine(x0, y0, x0 , y0 + CELL_SIZE - 1);

}

bool Cell::hasUpWall() const {
    return _upWall;
}

bool Cell::hasDownWall() const {
    return _downWall;
}

bool Cell::hasRightWall() const {
    return _rightWall;
}

bool Cell::hasLeftWall() const {
    return _leftWall;
}
