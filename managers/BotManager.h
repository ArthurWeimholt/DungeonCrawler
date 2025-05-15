// This class manages the bots by spawning, and updating them

#pragma once
#include "../entity/Bot.h"
#include "DungeonGrid.h"

class BotManager
{
public:
    BotManager(DungeonGrid& grid)
        : m_grid(grid)
    {}

    void spawn_bot(int y, int x, std::vector<Offset> shape, int color, int msec)
    {
        // Create a new bot and add it to the list
        auto bot = std::make_unique<Bot>(y, x, shape, color, msec);
        bot->draw();
        m_bots.push_back(std::move(bot));
    }

    void update_bots()
    {
        for (auto& bot : m_bots)
        {
            bot->update(m_grid);  // Update each bot
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
    DungeonGrid& m_grid;  // Reference to the grid for bot movement validation
    std::vector<std::unique_ptr<Bot>> m_bots;  // Vector to hold all bots
};
