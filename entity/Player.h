// This is a subclass of Entity to help with the logic of the player

#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
    Player() = default;
    Player(int y, int x, std::vector<Offset> shape, int color)
        : Actor(y, x, shape, color, 100) {}
};
