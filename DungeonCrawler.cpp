#include "pch.h"
#include "render/RenderGrid.h"
#include "render/AsciiArt.h"
#include "managers/BotManager.h"
#include "managers/GameManager.h"

void handle_exit(int signal);

int main()
{
    srand(time(0)); // Random seed

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);  // Enable arrow keys
    nodelay(stdscr, TRUE); // Non-blocking input

    RenderGrid::init_colors();

    signal(SIGINT, handle_exit); // Handle CTRL + C

    // Prompt Start and wait for user input
    draw_ascii_art_message(AsciiArt::menu_start_msg);
    clear();

    GameManager game;
    while (!game.is_game_over()) 
    {
        game.update(); // Updates the bots
        game.handle_input(getch()); // Handle user input
        refresh();                  // Update the screen
        usleep(10000);              // Sleep for 10ms
    }

    return 0;
}

void handle_exit(int sig) 
{
    (void)sig; // Suppress warning
    endwin();
    exit(0);
}
