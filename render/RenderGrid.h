// This file contains the drawing capability for the maze, human, and enemies
// Created by Arthur Weimholt

#pragma once
#include <array>
#include "../Constants.h"

struct Offset
{
    int dy;
    int dx;
    char symbol;
};

class RenderGrid
{
public:
    RenderGrid() {};
    ~RenderGrid() {};

    static void init_colors();
    static void draw_grid(const std::array<std::array<char, SCREEN_WIDTH>, SCREEN_HEIGHT>& grid);
    static void draw_entity(int y, int x, const std::vector<Offset>& shape, int color);
    static void draw_cell(int y, int x, char tile);

    // Render Menu functions
    static void draw_ascii_art(int y, int x, const std::vector<std::string>& art);
    static void draw_pause_menu(int highlight_index);

private:
    static int tile_to_color_pair(char tile);
};
