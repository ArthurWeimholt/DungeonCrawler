#include "pch.h"
#include "Bot.h"

Bot::Bot(int y, int x, std::vector<Offset> shape, const BotAttributes bot_attr)
        : Actor(y, x, shape, bot_attr.color, bot_attr.health), m_bot_attr(bot_attr), m_msec_timer(bot_attr.speed_ms)
{}

void Bot::update(const MovementValidator& movement)
{
    auto current_time = std::chrono::steady_clock::now();
    auto time_since_last_move = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_last_move_time).count();

    // Only move if enough time has passed (e.g., 500 ms)
    if (time_since_last_move > m_msec_timer) 
    {
        int dy = (rand() % 3) - 1; // -1, 0, or 1
        int dx = (rand() % 3) - 1;

        if (movement.can_move(y(), x(), dy, dx, m_shape))
        {
            move(dy, dx);
            draw();
        }

        // Only update the last movement time
        m_last_move_time = current_time;
    }
}

int Bot::roll_damage() const
{
    // This defines the range, add 1 since it is 0 based
    int range = (m_bot_attr.max_damage + 1 - m_bot_attr.min_damage);
    return (rand() % range) + m_bot_attr.min_damage; // min damage - max damage
}
