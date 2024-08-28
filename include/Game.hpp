#ifndef GAME_HPP
#define GAME_HPP
// #pragma once

#include <raylib-cpp.hpp>
#include <fstream>
#include <iostream>
#include "Player.hpp"
#include "BackGround.hpp"
#include "Asteroids.hpp"
#include "Bullet.hpp"

enum GameState {
    TITLESCREEN
    , PLAYING
    , PAUSED
    , GAMEOVER
};

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    int FPS;

    raylib::Window window;
    std::string title;
    bool startButtonClicked;

    //Background
    raylib::Texture BackGroundTexture;
    BackGround background;

    //States
    GameState currentState;

    //Player
    Player player;

    //Asteroids
    Asteroids* asteroids;
    int numberOfAsteroids;
    raylib::Texture AsteroidTexture;
    // raylib::Vector2 asteroidPos;
    float asteroidRadius;

    //Bullet
    Bullet* bullet;
    int maxBullets;

private:
    void processInput();
	void update();
	void render();

    void resetGame();
    int score;

    //Explosion
    raylib::Texture boomTexture;
    int frameCols;
    int frameRows;
    raylib::Vector2 frameSize;
    int currentFrame;
    int currentLine;
    raylib::Rectangle frameRect;
    raylib::Vector2 boomPos;
    bool boom;
    int frameCounter;
    Sound boomSound;
    Sound crashSound;
};

#endif