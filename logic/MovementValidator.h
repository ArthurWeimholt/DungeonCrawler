#pragma once

#include <vector>
#include "DungeonGrid.h"
#include "../Constants.h"

// Class Purpose: Enforce rules about where an entity is allowed to move, given the static grid layout.
// Responsibility: Checks collisions with the grid (like walls), not with other entities.

class MovementValidator
{
public:
    MovementValidator(const DungeonGrid& grid);

    bool can_move(int y, int x, int dy, int dx, const std::vector<Offset>& shape) const;

private:
    const DungeonGrid& m_grid;
};
