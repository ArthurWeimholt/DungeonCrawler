// This is a subclass of Entity to help with the logic of bot movement

#pragma once
#include <chrono>
#include "Entity.h"

class Bot : public Entity
{
public:

    Bot(int y, int x, std::vector<Offset> shape, int color, int msec)
        : Entity(y, x, shape, color), m_msec_timer(msec) // color pair RED for bots
    {
    }

    void update(const LogicalGrid& grid);
protected:
    int m_msec_timer; // Time for bot to move
    std::chrono::steady_clock::time_point m_last_move_time;  // Tracks last movement time
};
