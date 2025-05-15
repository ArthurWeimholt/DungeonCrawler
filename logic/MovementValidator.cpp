#include "pch.h"
#include "MovementValidator.h"

MovementValidator::MovementValidator(const DungeonGrid& grid)
    : m_grid(grid)
{}

// Checks to see if an entity can move in any direction legally
bool MovementValidator::can_move(int pos_y, int pos_x, int dy, int dx, const std::vector<Offset>& shape) const
{
    // Get grid layout 
    const auto& grid = m_grid.get_grid();

    // Iterate through all the parts of the entity to see if it would be an illegal move
    for (const auto& part : shape) 
    {
        int new_y = pos_y + part.dy + dy;
        int new_x = pos_x + part.dx + dx;

        if (new_y < 0 || new_y >= SCREEN_HEIGHT ||
            new_x < 0 || new_x >= SCREEN_WIDTH ||
            grid[new_y][new_x] != ' ')
        {
            return false;
        }
    }
    return true;
}
