// File contains ascii art and implementation for start 
#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>


class AsciiArt
{
public:
    // https://patorjk.com/software/taag/#p=display&f=Standard&t=%0A%0A
    static const std::vector<std::string> menu_start_msg;

    // Pause Menu
    static const std::vector<std::string> pause_menu;

    // Resume for menu
    static const std::vector<std::string> menu_resume_msg;

    // Quit for menu
    static const std::vector<std::string> menu_quit_msg;
};


inline void draw_ascii_art_message(const std::vector<std::string> message_lines) 
{
    size_t rows = message_lines.size();
    size_t cols = 0;
    for (const auto& line : message_lines) 
    {
        if (line.length() > cols) cols = line.length();
    }

    size_t start_y = (LINES - rows - 4) / 2;
    size_t start_x = (COLS - cols - 4) / 2;

    clear();

    // Draw the box with red color
    attron(COLOR_PAIR(1)); // Red box color
    for (size_t y = 0; y < rows + 4; ++y) 
    {
        for (size_t x = 0; x < cols + 4; ++x) 
        {
            if (y == 0 || y == rows + 3 || x == 0 || x == cols + 3)
                mvaddch(start_y + y, start_x + x, '*');
            else
                mvaddch(start_y + y, start_x + x, ' ');
        }
    }
    attroff(COLOR_PAIR(1)); // Turn off red color

    // Draw message
    attron(COLOR_PAIR(2)); // Blue text color
    for (size_t i = 0; i < rows; ++i) 
    {
        mvprintw(start_y + i + 2, start_x + 2, "%s", message_lines[i].c_str());
    }
    attroff(COLOR_PAIR(2));

    refresh();
    nodelay(stdscr, FALSE);
    getch();  // Wait for keypress
    nodelay(stdscr, TRUE);
}
