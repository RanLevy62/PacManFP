//
// Created by Ran Levy on 11/02/2021.
//

#pragma once

#include <chrono>
const int CELL_SIZE = 50;
const int BOARD_MARGIN = 5;
const int CELL_MARGIN = 1;

const float STEP_SIZE = 0.1;
const int GAME_LOOP_INTERVAL_MS = 100;

enum Direction {
    Up,
    Down,
    Left,
    Right
};

