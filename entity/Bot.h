// This is a subclass of Entity to help with the logic of bot movement

#pragma once
#include <chrono>
#include "Actor.h"
#include "logic/MovementValidator.h"

class Bot : public Actor
{
public:

    Bot(int y, int x, std::vector<Offset> shape, int color, int msec)
        : Actor(y, x, shape, color, 100), m_msec_timer(msec) // color pair RED for bots
    {
    }

    void update(const MovementValidator& movement);
protected:
    int m_msec_timer; // Time for bot to move
    std::chrono::steady_clock::time_point m_last_move_time;  // Tracks last movement time
};
