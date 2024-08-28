#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Player.hpp"
#include "Game.hpp"

class Collision
{
public:
    static void againstWalls(const float dimension, raylib::Vector2& position);
  
private:
};

#endif