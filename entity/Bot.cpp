#include "pch.h"
#include "Bot.h"

void Bot::update(const LogicalGrid& grid)
{
    auto current_time = std::chrono::steady_clock::now();
    auto time_since_last_move = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_last_move_time).count();

    // Only move if enough time has passed (e.g., 500 ms)
    if (time_since_last_move > m_msec_timer) 
    {
        int dy = (rand() % 3) - 1; // -1, 0, or 1
        int dx = (rand() % 3) - 1;

        if (grid.can_move(y(), x(), dy, dx, m_shape))
        {
            clear();
            move(dy, dx);
            draw();
        }

        // Only update the last movement time
        m_last_move_time = current_time;
    }
}
