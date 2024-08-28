#include "../include/Player.hpp"
#include "math.h"
#include "../include/Collisions.hpp"

Player::Player()
    : position((raylib::Vector2){0, 0})
    , speed(5.0f)
    , scale(0.07f)
    , base(25.0f)
    , color(raylib::RED)
    , velocity((raylib::Vector2){0, 0})
{
    init();
    height = (base / 2) / tanf(24*DEG2RAD);
    float offsetX = sin(rotation * DEG2RAD) * (height / 2.5f);
    float offsetY = -cos(rotation * DEG2RAD) * (height / 2.5f);
    collider = Vector3{position.x + offsetX, position.y + offsetY, 12.0f};
}

void Player::init()
{
    position = (raylib::Vector2){(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    acceleration = 0.0f;
    rotation = 0.0f;
}


Player::~Player() 
{
    // UnloadTexture(texture);
}

void Player::draw()
{
    //Player
    raylib::Vector2 s1 = {position.x + sinf(rotation*DEG2RAD)*(height), position.y - cosf(rotation*DEG2RAD)*(height) };
    raylib::Vector2 s2 = {position.x - cosf(rotation*DEG2RAD)*(base/2), position.y - sinf(rotation*DEG2RAD)*(base/2) };
    raylib::Vector2 s3 = {position.x + cosf(rotation*DEG2RAD)*(base/2), position.y + sinf(rotation*DEG2RAD)*(base/2) };
    DrawTriangle(s1, s2, s3, color);
}

void Player::update()
{
    processEvents();

    Acceleration_Deacceleration();

    position.x += acceleration * velocity.x;
    position.y -= acceleration * velocity.y;

    Collision::againstWalls(height, position);
}


void Player::processEvents()
{
    if (IsKeyDown(KEY_A))
        rotation -= 5;

    if (IsKeyDown(KEY_D))
        rotation += 5;
}

// No Backward movement
void Player::Acceleration_Deacceleration()
{
    velocity.x = sin(rotation*DEG2RAD)* speed;
    velocity.y = cos(rotation*DEG2RAD)* speed;

    if (IsKeyDown('W')) 
    {
        if (acceleration < 1)
            acceleration += 0.02f;
    }

    else
    {
        if (acceleration > 0)
            acceleration -= 0.02f;

        else if (acceleration < 0)
            acceleration = 0;
    }

    if (IsKeyDown('S'))
    {
        if (acceleration > 0) 
            acceleration -= 0.02f;

        else if (acceleration < 0) 
            acceleration = 0;
    }
}

float Player::getSpeed()
{
    return speed;
}

raylib::Vector2 Player::getPos()
{
    return position;
}

float Player::getHeight()
{
    return height;
}

float Player::getRotation()
{
    return rotation;
}