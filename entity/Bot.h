// This is a subclass of Entity to help with the logic of bot movement

#pragma once
#include <chrono>
#include "Actor.h"
#include "logic/MovementValidator.h"

struct BotAttributes
{
    std::string name; // type of bot
    int max_damage;   // max damage this bot can dish out
    int min_damage;   // min damage this bot can dish out
    int speed_ms;     // how long before it can move again in ms
    int health;       // health
    int color;        // color of the bot
};

class Bot : public Actor
{
public:
    Bot(int y, int x, std::vector<Offset> shape, const BotAttributes bot_attr);
    virtual ~Bot() = default;

    // Virtual functions
    virtual void update(const MovementValidator& movement);
    virtual int roll_damage() const;

protected:
    BotAttributes m_bot_attr;
    int m_msec_timer; // Time for bot to move
    std::chrono::steady_clock::time_point m_last_move_time;  // Tracks last movement time
};
