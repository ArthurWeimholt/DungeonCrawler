
#pragma once

#define BLACK 0
#define RED 1
#define BLUE 2
#define MAGENTA 3
#define CYAN 4
#define YELLOW 5
#define GREEN 6

const int MAX_HUMAN_HEIGHT = 2; // Human height '0' indexed

const int ROOM_WIDTH = 5;       // Room width
const int ROOM_HEIGHT = 5;      // Room height
const int WALL = 1;             // Wall thickness

const int MAZE_WIDTH = 25;      // number of rooms horizontally
const int MAZE_HEIGHT = 10;     // number of rooms vertically

const int SCREEN_WIDTH = MAZE_WIDTH * (ROOM_WIDTH + WALL) + WALL;
const int SCREEN_HEIGHT = MAZE_HEIGHT * (ROOM_HEIGHT + WALL) + WALL;
