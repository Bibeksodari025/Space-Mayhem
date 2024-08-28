#ifndef BULLET_HPP
#define BULLET_HPP

#include <raylib-cpp.hpp>
#include "../include/Player.hpp"

class Player;

class Bullet
{
public:
    Bullet();

    void draw();
    void update();
    void init();
    raylib::Vector2 getPos();
    float getRadius();
    void activate(Player& player);

    bool getStatus();


private:
    raylib::Vector2 position;
    raylib::Vector2 velocity;

    int shoots;
    float radius;
    float rotation;
    bool active;
    raylib::Color color;
    float speed;

    raylib::Texture texture;
    raylib::Vector2 origin;
};

#endif