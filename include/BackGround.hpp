#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <raylib-cpp.hpp>

class BackGround
{
public:
    BackGround(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip);
    void draw();
private:
    raylib::Texture* _texture;
    raylib::Rectangle InClip;
    raylib::Rectangle OutClip;
};

#endif