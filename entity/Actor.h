#pragma once

#include "Entity.h"
#include <vector>
#include <algorithm>

class Actor : public Entity
{
public:
    Actor() = default;
    Actor(int y, int x, std::vector<Offset> shape, int color, int health)
        : Entity(y, x, shape, color), m_health(health) {};

    inline void take_damage(int amount) { m_health = std::max(0, m_health - amount); };
    inline bool is_dead() { return m_health <= 0; }

protected:
    int m_health;
};