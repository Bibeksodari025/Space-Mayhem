#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <raylib-cpp.hpp>

class Asteroids
{
public:
    Asteroids();
    ~Asteroids();

    void init();
    void draw();
    void update();
    void destroy();

    void setRadius(float r);
    bool getStatus();
    raylib::Vector2 getPos();

private:
    raylib::Vector2 position;
    raylib::Vector2 velocity;
    float radius;
    bool active;
    float danger;
    float speed;
    raylib::Vector2 origin;

    raylib::Texture texture;
};

#endif