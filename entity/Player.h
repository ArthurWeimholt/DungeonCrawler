// This is a subclass of Entity to help with the logic of the player

#pragma once
#include <chrono>
#include "Entity.h"

class Player : public Entity
{
public:
    Player() = default;
    Player(int y, int x, std::vector<Offset> shape, int color)
        : Entity(y, x, shape, color)
    {
    }
};
