#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib-cpp.hpp>

class Bullet;

class Player
{
public:
    Player();
    ~Player();
    void draw();
    void update();
    void init();

    float getSpeed();
    raylib::Vector2 getPos();
    float getHeight();
    float getRotation();

private:
    void processEvents();
    void Acceleration_Deacceleration();

private:
    float speed;
    float acceleration;
    float rotation;
    float scale;
    raylib::Vector2 velocity;
    raylib::Vector2 position;

    raylib::Color color;
    raylib::Vector3 collider;
    float base;
    float height;

};

#endif