#include "pch.h"
#include "RenderGrid.h"
#include "AsciiArt.h"

void RenderGrid::init_colors()
{
    start_color(); // Initialize color functionality

    // Create color pairs
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);  // Red box
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK); // Blue ASCII text
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
}

// Draws the entity figure
void RenderGrid::draw_entity(int y, int x, const std::vector<Offset>& shape, int color) 
{
    attron(COLOR_PAIR(color));
    for (const auto& part : shape)
    {
        draw_cell(y + part.dy, x + part.dx, part.symbol);
    }
    attroff(COLOR_PAIR(color));
}

// Draws the current state of the maze/grid
void RenderGrid::draw_grid(const std::array<std::array<char, SCREEN_WIDTH>, SCREEN_HEIGHT> &grid)
{
    attron(COLOR_PAIR(3));
    for (int y = 0; y < SCREEN_HEIGHT; ++y) 
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x) 
        {
            mvaddch(y, x, grid[y][x]);
        }
    }
    attroff(COLOR_PAIR(3));
}

void RenderGrid::draw_cell(int y, int x, char tile)
{
    if (y < 0 || y >= SCREEN_HEIGHT || x < 0 || x >= SCREEN_WIDTH)
    {
        return; // Prevent out-of-bounds access
    }

    int color = tile_to_color_pair(tile);

    attron(COLOR_PAIR(color));
    mvaddch(y, x, tile);
    attroff(COLOR_PAIR(color));
}

int RenderGrid::tile_to_color_pair(char tile)
{
    switch (tile)
    {
        case '#': return MAGENTA;
        case ' ': return BLACK; 
        //case TileType::Door:  return 2;
        //case TileType::Trap:  return 3;
        //case TileType::Goal:  return 4;
        default:  return BLACK; // default pair
    }
}

void RenderGrid::draw_ascii_art(int y, int x, const std::vector<std::string>& art)
{
    for (size_t i = 0; i < art.size(); ++i)
    {
        mvprintw(y + i, x, "%s", art[i].c_str());
    }
}

void RenderGrid::draw_pause_menu(int highlight_index)
{
    clear();

    const auto& title_art = AsciiArt::pause_menu;
    const auto& resume_art = AsciiArt::menu_resume_msg;
    const auto& quit_art = AsciiArt::menu_quit_msg;

    int box_width = 50;
    int art_left_padding = 2;

    int total_height = static_cast<int>(title_art.size() + resume_art.size() + quit_art.size() + 3); // 3 lines: padding & separator
    int start_y = (LINES - total_height) / 2;
    int start_x = (COLS - box_width) / 2;

    // Draw outer box (single box around everything)
    attron(COLOR_PAIR(YELLOW));
    for (int i = 0; i < total_height + 2; ++i)
    {
        mvaddch(start_y + i - 1, start_x - 1, '|');
        mvaddch(start_y + i - 1, start_x + box_width, '|');
    }
    for (int j = 0; j <= box_width; ++j)
    {
        mvaddch(start_y - 1, start_x + j, '-');
        mvaddch(start_y + total_height, start_x + j, '-');
    }
    mvaddch(start_y - 1, start_x - 1, '+');
    mvaddch(start_y - 1, start_x + box_width, '+');
    mvaddch(start_y + total_height, start_x - 1, '+');
    mvaddch(start_y + total_height, start_x + box_width, '+');

    attroff(COLOR_PAIR(YELLOW));
    int cursor_y = start_y;

    // Draw title left aligned
    draw_ascii_art(cursor_y, start_x + art_left_padding, title_art);
    cursor_y += title_art.size();

    attron(COLOR_PAIR(YELLOW));
    // Draw horizontal line under title
    for (int j = 0; j < box_width; ++j)
    {
        mvaddch(cursor_y, start_x + j, '-');
    }
    attroff(COLOR_PAIR(YELLOW));
    ++cursor_y;

    // Highlight Resume block
    for (size_t i = 0; i < resume_art.size(); ++i)
    {
        if (highlight_index == 0)
            attron(A_REVERSE);

        // Fill entire row with spaces to highlight full width
        mvhline(cursor_y + i, start_x, ' ', box_width);

        // Draw ASCII line on top
        mvprintw(cursor_y + i, start_x + art_left_padding, "%s", resume_art[i].c_str());

        if (highlight_index == 0)
            attroff(A_REVERSE);
    }
    cursor_y += resume_art.size();

    // Highlight Quit block
    for (size_t i = 0; i < quit_art.size(); ++i)
    {
        if (highlight_index == 1)
            attron(A_REVERSE);

        mvhline(cursor_y + i, start_x, ' ', box_width);
        mvprintw(cursor_y + i, start_x + art_left_padding, "%s", quit_art[i].c_str());

        if (highlight_index == 1)
            attroff(A_REVERSE);
    }

    refresh();
}
