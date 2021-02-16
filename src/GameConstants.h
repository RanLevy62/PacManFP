//
// Created by Ran Levy on 11/02/2021.
//

#pragma once

#include <chrono>
const int CELL_SIZE = 100;
const int BOARD_MARGIN = 5;
const int CELL_MARGIN = 2;

const float STEP_SIZE = 0.1;
const int GAME_LOOP_INTERVAL_MS = 100;

enum Direction {
    Up,
    Down,
    Left,
    Right
};

//Direction reverseDirection(Direction dir) {
//    switch (dir) {
//        case Up: return Down;
//        case Down: return Up;
//        case Right: return Left;
//        case Left: return Right;
//    }
//}