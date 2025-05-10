#include "pch.h"
#include "Entity.h"


Entity::Entity(int y, int x, std::vector<Offset> shape, int color)
		: m_y(y), m_x(x), m_shape(shape), m_color(color){}

void Entity::draw() const
{
    RenderGrid::draw_entity(m_y, m_x, m_shape, m_color);
}

void Entity::clear() const
{
    for (const auto& part : m_shape)
    {
        RenderGrid::draw_cell(m_y + part.dy, m_x + part.dx, ' ');
    }
}

void Entity::move(int dy, int dx)
{
    clear();
    m_y += dy;
    m_x += dx;
    draw();
}
