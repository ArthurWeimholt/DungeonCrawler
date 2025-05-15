// This file contains the drawing logic definitions for the maze
// Created by Arthur Weimholt

#include "pch.h"
#include "DungeonGrid.h"
#include "../render/RenderGrid.h"

DungeonGrid::DungeonGrid()
{
    initialize_grid();    // Initialize maze
    generate_grid(0, 0);  // Generate maze by tearing down walls
}

// Draws walls everywhere initially
void DungeonGrid::initialize_grid() 
{
    for (int y = 0; y < SCREEN_HEIGHT; y++) 
    {
        for (int x = 0; x < SCREEN_WIDTH; x++) 
        {
            // If room height + wall is 0 or room width + wall is 0 then lets add a wall
            if (y % (ROOM_HEIGHT + WALL) == 0 || x % (ROOM_WIDTH + WALL) == 0) 
            {
                m_maze[y][x] = '#';  // Set wall
            } else 
            {
                m_maze[y][x] = ' ';  // Set hallway
            }
        }
    }
}

// Function to "knock down" a wall between two rooms
void DungeonGrid::remove_wall_between(int room_y, int room_x, int dy, int dx)
{
    // Start at the top-left corner of the current room
    int y = room_y * (ROOM_HEIGHT + WALL) + WALL;
    int x = room_x * (ROOM_WIDTH + WALL) + WALL;

    if (dy == 1) // moving down
    {
        // Knock down the wall BELOW the room
        for (int i = 0; i < ROOM_WIDTH; ++i)
        {
            m_maze[y + ROOM_HEIGHT][x + i] = ' ';
        }
    }
    else if (dy == -1) // moving up
    {
        // Knock down the wall ABOVE the room
        for (int i = 0; i < ROOM_WIDTH; ++i)
        {
            m_maze[y - WALL][x + i] = ' ';
        }
    }
    else if (dx == 1) // moving right
    {
        // Knock down the wall to the RIGHT of the room
        for (int i = 0; i < ROOM_HEIGHT; ++i)
        {
            m_maze[y + i][x + ROOM_WIDTH] = ' ';
        }
    }
    else if (dx == -1) // moving left
    {
        // Knock down the wall to the LEFT of the room
        for (int i = 0; i < ROOM_HEIGHT; ++i)
        {
            m_maze[y + i][x - WALL] = ' ';
        }
    }
}

// Takes the rooms generated and knocks down walls recursively to generate a maze
void DungeonGrid::generate_grid(int y, int x) 
{
    m_rooms_visited[y][x] = true;

    // Initialize direction array: right, down, left, and up
    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    // Randomly shuffle direction array
    for (int i = 0; i < 4; ++i) 
    {
        int r = rand() % 4;
        std::swap(dirs[i], dirs[r]);
    }

    // Calculate the neighbor's position (ny, nx) based on the direction.
    for (int i = 0; i < 4; ++i) 
    {
        int dy = dirs[i][0];
        int dx = dirs[i][1];
        int ny = y + dy;
        int nx = x + dx;

        // Check if the neighbor is within bounds and hasn't been visited yet
        if (ny >= 0 && ny < MAZE_HEIGHT && nx >= 0 && nx < MAZE_WIDTH && !m_rooms_visited[ny][nx]) 
        {
            remove_wall_between(y, x, dy, dx); // Remove wall between current position and neighbor
            
            // DEBUG VISUALIZATION
            RenderGrid::draw_grid(m_maze);
            refresh();
            usleep(10000);

            generate_grid(ny, nx);
        }
    }
}
