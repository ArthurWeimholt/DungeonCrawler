#pragma once
#include <array>
#include <vector>
#include "../render/RenderGrid.h"
#include "../Constants.h"

// This class generates the dungeon grid layout

class DungeonGrid
{
public:
	DungeonGrid();
	~DungeonGrid(){};

	// Grid generation 
	void initialize_grid();
	void remove_wall_between(int room_y, int room_x, int dy, int dx);
	void generate_grid(int y, int x);

	// Getters
	const std::array<std::array<char, SCREEN_WIDTH>, SCREEN_HEIGHT>& get_grid() const { return m_maze; }

private:
	// Member variables
	std::array<std::array<char, SCREEN_WIDTH>, SCREEN_HEIGHT> m_maze;
	bool m_rooms_visited[MAZE_HEIGHT][MAZE_WIDTH] = {{false}};
};

