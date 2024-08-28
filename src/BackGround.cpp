#include "../include/BackGround.hpp"

BackGround::BackGround(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip)
    : _texture(texture)
    , InClip(inClip)
    , OutClip(outClip)
{}

void BackGround::draw()
{
    _texture->Draw(InClip, OutClip);
}