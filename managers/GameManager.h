#pragma once
#include "BotManager.h"
#include "../entity/Player.h"
#include "../logic/LogicalGrid.h"
#include "../sounds/SoundPlayer.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void update();              // Updates bots, handles collisions
    void handle_input(int ch);  // Handles user input
    void draw();                // Draws player + bots

    void cleanup(); 
    bool is_game_over() const { return m_game_over; }

private:
    void initialize_player();
    void spawn_bots(int count, int msec);
    bool check_collision(const Entity& a, const Entity& b) const;
    void handle_collisions();
    bool pause_menu(); // true for resume, false for quit

    // Manages the logical grid, player and bot manager
    DungeonGrid m_grid;
    Player m_player;
    BotManager m_bot_manager;
    SoundPlayer m_sound;

    bool m_game_over;
};
