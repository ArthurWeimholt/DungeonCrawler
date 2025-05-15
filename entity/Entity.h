#pragma once
#include "../render/RenderGrid.h"

// Entity can be human, sprite, item, or doors
// This serves as the base for spatial, movable, and drawable things

class Entity
{
public:
	Entity() = default;
	Entity(int y, int x, std::vector<Offset> shape, int color);
    virtual ~Entity() {};

	virtual void draw() const;
	virtual void clear() const;
	virtual void move(int dy, int dx);

	inline int y() const { return m_y; }
	inline int x() const { return m_x; }

	const std::vector<Offset>& get_shape() const { return m_shape; }

protected:
	int m_y;
	int m_x;
	std::vector<Offset> m_shape;
	int m_color;
};