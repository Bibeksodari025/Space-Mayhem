#include "../include/Asteroids.hpp"
#include "../include/Collisions.hpp"

Asteroids::Asteroids()
    : radius(0.0f)
    , active(false)
    , velocity((raylib::Vector2){0, 0})
    , speed(2.0f)
    , texture("assets/Texture_Asteroids/asteroid.png")
    , origin((raylib::Vector2){0, 0})
{
    init();
}

bool Asteroids::getStatus()
{
    return active;
}

raylib::Vector2 Asteroids::getPos()
{
    return position;
}

Asteroids::~Asteroids()
{
    texture.Unload();
}

void Asteroids::init()
{
    do {
        position.x = GetRandomValue(0, GetScreenWidth());
    } while ((position.x > GetScreenWidth() / 2 - 150) && (position.x < GetScreenWidth() / 2 + 150));
    
    do {
        position.y = GetRandomValue(0, GetScreenHeight());
    } while ((position.y > GetScreenHeight() / 2 - 150) && (position.y < GetScreenHeight() / 2 + 150));

    do {
        velocity.x = GetRandomValue(-speed, speed);
        velocity.y = GetRandomValue(-speed, speed);
    } while (velocity.x == 0 && velocity.y == 0);

    active = true;
}

void Asteroids::destroy()
{
    active = false;
}

void Asteroids::setRadius(float r)
{
    radius = r;
}

void Asteroids::update()
{
    position.x += velocity.x;
    position.y += velocity.y;

    Collision::againstWalls(radius, position);
}

void Asteroids::draw()
{
    raylib::Rectangle inClip(0, 0, texture.width, texture.height);
    raylib::Rectangle outClip(position.x - radius, position.y - radius, 2.0f * radius, 2.0f * radius);
    texture.Draw(inClip, outClip, origin, 0.0f, RAYWHITE);
        
    DrawCircleLinesV(position, radius, RED);
    
    //     texture.Unload();
    //     DrawCircleV(position, radius, Fade(LIGHTGRAY, 0.3f));
}