# PacMan Final Project

This is a (very) simplifies version of the old PacMan game, submitted as the capstone project of my c++ course.
The project was built from scratch by me.

### Building instructions

To build the project:
1. Either create a new build directory, or use the directory 'build' already set-up in the workspace.
2. cd to the build directory.
3 cmake .. and then (after configuration is complete) 'make'.
   

The program should compile error-free.
   
### Running the game 

Start the game from within the build directory by ./PacManFP, and the switch to the desktop.
The users controls the PacMan with the arrow keys. Other controls: 'q' to quit the game, 'p' to pause and 'r' to resume after pause.


### Project description

The main.cpp file is the program entry point. It loops over a text based menu that allows to user to select game or to quit. This text screen is used when game is over to show score.
The  Game class is the main class of this game. it holds the game board (which is the PacMan maze, a 2d array of Cell Objects to be described later) and the 5 creatures moving inside the maze - the PacMan and the 4 ghosts chasing it.
The game class is called first  to initGameData - this function accepts the name of a file containing the game data (Format  of this file is described in code comments). It reads the file, initializes the data and draws the game board. Then  starts the game loop.
In each game loop iteration - each creature moves in its direction. when a creature is at the center of a new cell, if it can continue moving in the same direction it does so.
For a ghost - if it can not continue moving in the same direction (because of a wall), a new available random direction is set for it.
For the PacMan - if the user chooses a new available direction, the PacMan starts moving in that direction. If the new direction is blocked - the PacMan stops.
The game continues until one of the ghosts catches the PacMan.
Game score is the number of seconds until the PacMan is caught.

### rubric points addressed

All README requirements where addressed. This file contains building / running instructions, software description and a
list (this list) of rubric points addressed.

Compiling requirements are addressed. The project is built / compiled by cmake / make.

At least 5 rubric requirements:
1. The project demonstrates c++ functions and control structures: Functions, range loops, and other advanced c++ features are used.
2. The project reads data (the Pacman game description) from file and processes this data.
3. The project accepts user inputs (from 2 screens - user selection commands from a text screen and game commands from a graphics screen) and  processes this input.
4. The project uses OOP techniques - The project is organized using classes with class attributes holding data and class methods  to preform tasks.
5. Classes use appropriate access specifiers.
6. Class constructors utilize member initialization lists.
7. Classes follow inheritance hierarchy. Specifically - both PacMan and the ghosts inherit common behaviour from Creature.
8. Derived class functions (specifically the function move()) override  base class functions.
9. The  project  uses destructors to deallocate resources.
10. The project uses smart pointers instead of raw pointers. Specifically - SDL resources (which are raw pointers) are encapsulated into smart pointers.



