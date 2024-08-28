#include "../include/Collisions.hpp"

#include <iostream>

void Collision::againstWalls(const float dimension, raylib::Vector2& position)
{
    // Horizontal
    if (position.x > GetScreenWidth() + dimension)
        position.x = -dimension;

    else if (position.x < -(dimension))
        position.x = GetScreenWidth() + dimension;
    
    //Vertical
    if (position.y > (GetScreenHeight() + dimension))
        position.y = -(dimension);
            
    else if (position.y < -(dimension)) 
        position.y = GetScreenHeight() + dimension;
}
