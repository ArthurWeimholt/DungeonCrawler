// This file containes the drawing logic declarations
// Created by Arthur Weimholt

#pragma once
#include <array>
#include <vector>
#include "../render/RenderGrid.h"
#include "../Constants.h"

class DungeonGrid
{
public:
	DungeonGrid();
	~DungeonGrid(){};

	// Grid generation 
	void initialize_grid();
	void remove_wall_between(int room_y, int room_x, int dy, int dx);
	void generate_grid(int y, int x);

	// Can move logic
	bool can_move(int pos_y, int pos_x, int dy, int dx, const std::vector<Offset>& shape) const;

	// Getters
	const std::array<std::array<char, SCREEN_WIDTH>, SCREEN_HEIGHT>& get_grid() const { return m_maze; }

private:
	// Member variables
	std::array<std::array<char, SCREEN_WIDTH>, SCREEN_HEIGHT> m_maze;
	bool m_rooms_visited[MAZE_HEIGHT][MAZE_WIDTH] = {{false}};
};

