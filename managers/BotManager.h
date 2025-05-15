// This class manages the bots by spawning, and updating them

#pragma once
#include "../entity/Bot.h"
#include "DungeonGrid.h"

class BotManager
{
public:
    BotManager() = default;

    void spawn_bot(int y, int x, std::vector<Offset> shape, BotAttributes bot_attr)
    {
        // Create a new bot and add it to the list
        auto bot = std::make_unique<Bot>(y, x, shape, bot_attr);
        bot->draw();
        m_bots.push_back(std::move(bot));
    }

    void update_bots(MovementValidator& movement)
    {
        for (auto& bot : m_bots)
        {
            bot->update(movement);  // Update each bot
        }
    }

    void draw_bots()
    {
        for (auto& bot : m_bots)
        {
            bot->draw();
        }
    }

    const std::vector<std::unique_ptr<Bot>>& get_bots() const { return m_bots; }

private:
    std::vector<std::unique_ptr<Bot>> m_bots;  // Vector to hold all bots
};
