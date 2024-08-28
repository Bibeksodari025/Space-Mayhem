#include "../include/Bullet.hpp"
#include "../include/Collisions.hpp"

Bullet::Bullet()
    : radius(3.0f)
    , shoots(10)
    , speed(1.5f)
    , color(raylib::YELLOW)
    , texture("assets/Bullet.png")
    , origin((raylib::Vector2){0, 0})
{
    init();
}

void Bullet::init()
{
    velocity = (raylib::Vector2){0, 0};
    position = (raylib::Vector2){0, 0};
    active = false;
}

void Bullet::update()
{
    position.x += velocity.x;
    position.y -= velocity.y;

    if (position.x < 0 || position.x > GetScreenWidth() || position.y < 0 || position.y > GetScreenHeight()) 
    {
        init();
    }
    // Collision::againstWalls(radius, position);
}

void Bullet::activate(Player& player)
{
    position = (raylib::Vector2){ player.getPos().x + sin(player.getRotation() * DEG2RAD) * player.getHeight(), player.getPos().y - cos(player.getRotation() * DEG2RAD) * player.getHeight() };
    active = true;
    velocity.x = sin(player.getRotation() * DEG2RAD) * player.getSpeed() * speed;
    velocity.y = cos(player.getRotation() * DEG2RAD) * player.getSpeed() * speed;
    rotation = player.getRotation();
}

raylib::Vector2 Bullet::getPos()
{
    return position;
}

float Bullet::getRadius()
{
    return radius;
}

bool Bullet::getStatus()
{
    return active;
}

void Bullet::draw()
{
    DrawCircleV(position, radius, color);

    raylib::Rectangle inClip(180, 164, 188, 172);
    raylib::Rectangle outClip(position.x - radius, position.y - radius, 2.0f * radius, 2.0f * radius);
    texture.Draw(inClip, outClip, origin, 0.0f, RAYWHITE);

}