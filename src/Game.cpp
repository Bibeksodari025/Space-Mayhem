#include "../include/Game.hpp"
#include <string>

Game::Game()
    : title("SPACE MAYHEM")
    , window(1240, 680, title)
    , FPS(60)
    , currentState(TITLESCREEN)
    , BackGroundTexture("assets/bg_space.png")
    , background(&BackGroundTexture, raylib::Rectangle(0, 0, 522, 228), raylib::Rectangle(0, 0, GetScreenWidth(), GetScreenHeight()))
    , numberOfAsteroids(6)
    , asteroidRadius(50.0f)
    , smallAsteroidRadius(25.0f)
    , maxBullets(20)
    , startButtonClicked(false)
    , score(0)
    , boomTexture("assets/explosion.png")
    , frameCols(5)
    , frameRows(5)
    , currentFrame(0)
    , currentLine(0)
    , frameSize((raylib::Vector2){(float)(boomTexture.width / frameCols), (float)(boomTexture.height / frameRows)})
    , boomPos((raylib::Vector2){0.f, 0.f})
    , frameRect(0, 0, frameSize.x, frameSize.y)
    , boom(false)
    , frameCounter(0)
{
    SetTargetFPS(FPS);

    //Explosion Sound
    InitAudioDevice();
    boomSound = LoadSound("assets/boom.wav");
    crashSound = LoadSound("assets/crash.wav");

    asteroids = new Asteroids[numberOfAsteroids];
    for (int i = 0; i < numberOfAsteroids; i++)
    {
        asteroids[i].setRadius(asteroidRadius);
    }

    smallAsteroids = new Asteroids[numberOfAsteroids];
    for (int i = 0; i < numberOfAsteroids; i++)
    {
        smallAsteroids[i].setRadius(smallAsteroidRadius);
    }

    //Bullets
    bullet = new Bullet[maxBullets];    
}

Game::~Game()
{
    delete[] asteroids;
    delete[] smallAsteroids;
    delete[] bullet;
    UnloadTexture(boomTexture);
    UnloadSound(boomSound); 
    UnloadSound(crashSound); 
    CloseAudioDevice();
}


void Game::processInput()
{
    switch (currentState)
    {
        case TITLESCREEN:
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = PLAYING;
            }
            break;
        case PAUSED:
            if (IsKeyPressed(KEY_P))
                currentState = PLAYING;
            break;

        case PLAYING:
            if (IsKeyPressed(KEY_P))
                currentState = PAUSED;

            //Bullets
            if (IsKeyPressed(KEY_SPACE))
            {
                for (int i = 0; i < maxBullets; i++)
                {
                    if (!bullet[i].getStatus())
                    {
                        bullet[i].activate(player);
                        break;
                    }
                }
            }

            break;

        case GAMEOVER:
            if (IsKeyPressed(KEY_ENTER))
            {
                resetGame();
                currentState = PLAYING;
            }
            break;
    }
}


void Game::update()
{
    processInput();
    switch (currentState)
    {
        case TITLESCREEN:
            break;
        case PAUSED:
            break;
        
        case PLAYING:
            player.update();

            //Asteroids
            for (int i = 0; i < numberOfAsteroids; i++)
            {
                if (asteroids[i].getStatus()) 
                    asteroids[i].update();

                else
                    asteroids[i].init();
            }

            for (int i = 0; i < numberOfAsteroids; i++)
            {
                if (smallAsteroids[i].getStatus()) 
                    smallAsteroids[i].update();

                else
                    smallAsteroids[i].init();
            }

            //Bullet
            for (int i = 0; i < maxBullets; i++)
            {
                bullet[i].update();
            }

            //Collisions
            for (int i = 0; i < maxBullets; i++)
            {
                if (bullet[i].getStatus())
                {
                    for (int j = 0; j < numberOfAsteroids; j++)
                    {
                        if (asteroids[j].getStatus() && CheckCollisionCircles(bullet[i].getPos(), bullet[i].getRadius(), asteroids[j].getPos(), asteroidRadius))
                        {
                            asteroids[j].destroy();
                            boomPos = asteroids[j].getPos();
                            boomPos.x -= frameSize.x / 2.0f;
                            boomPos.y -= frameSize.y / 2.0f;
                            boom = true;
                            PlaySound(boomSound);
                            bullet[i].init();
                            score += 1;
                            break;
                        }

                        if (smallAsteroids[j].getStatus() && CheckCollisionCircles(bullet[i].getPos(), bullet[i].getRadius(), smallAsteroids[j].getPos(), smallAsteroidRadius))
                        {
                            smallAsteroids[j].destroy();
                            boomPos = smallAsteroids[j].getPos();
                            boomPos.x -= frameSize.x / 2.0f;
                            boomPos.y -= frameSize.y / 2.0f;
                            boom = true;
                            PlaySound(boomSound);
                            bullet[i].init();
                            score += 1;
                            break;
                        }
                    }
                }
            }

            if (boom)
            {
                frameCounter++;

                if (frameCounter > 2)
                {
                    currentFrame++;
                    if (currentFrame >= frameCols)
                    {
                        currentFrame = 0;
                        currentLine++;

                        if (currentLine >= frameRows)
                        {
                            currentLine = 0;
                            boom = false;
                        }
                    }
                    frameCounter = 0;
                }
            }
            frameRect.x = frameSize.x * currentFrame;
            frameRect.y = frameSize.y * currentLine;

            for (int i = 0; i < numberOfAsteroids; i++)
            {
                if (asteroids[i].getStatus() && CheckCollisionCircles(player.getPos(), player.getHeight() / 2, asteroids[i].getPos(), asteroidRadius))
                {
                    PlaySound(crashSound);
                    currentState = GAMEOVER;
                    break;
                }
            }

            for (int i = 0; i < numberOfAsteroids; i++)
            {
                if (smallAsteroids[i].getStatus() && CheckCollisionCircles(player.getPos(), player.getHeight() / 2, smallAsteroids[i].getPos(), smallAsteroidRadius))
                {
                    PlaySound(crashSound);
                    currentState = GAMEOVER;
                    break;
                }
            }

            break;

        case GAMEOVER:
            break;
    }
}

void Game::render() 
{
    std::string controls1 = "W ->\nA ->\nS ->\nD ->\nP ->";
    std::string controls2 = "accelerate\nLeft Turn\nRight Turn\ndeaccelerate\nPause";
    window.ClearBackground(raylib::RAYWHITE);
    background.draw();
    
    std::string scoreText;

    switch (currentState)
    {
        case TITLESCREEN:
            {
                // window.ClearBackground(raylib::RAYWHITE);
                int fontSize = 80;
                DrawText(title.c_str(), (GetScreenWidth() - MeasureText(title.c_str(), fontSize)) / 2, GetScreenHeight() / 2 - fontSize / 2, fontSize, WHITE);
                DrawText("PRESS ENTER TO CONTINUE", GetScreenWidth()/2 - MeasureText("PRESS ENTER TO CONTINUE", 20)/2, 400, 20, YELLOW);
            }      
            break;
      
        case PAUSED:
            DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 40) / 2, 200, 40, WHITE);
            DrawText("PRESS [P] TO RESUME", GetScreenWidth()/2 - MeasureText("PRESS [P] TO RESUME", 20)/2, GetScreenHeight()/2 + 100, 20, YELLOW);

        case PLAYING:

            player.draw();

            for (int i = 0; i < numberOfAsteroids; i++)
            {
                if (asteroids[i].getStatus())
                    asteroids[i].draw();
            }

            for (int i = 0; i < numberOfAsteroids; i++)
            {
                if (smallAsteroids[i].getStatus())
                    smallAsteroids[i].draw();
            }

            //Bullet
            for (int i = 0; i < maxBullets; i++)
            {
                if (bullet[i].getStatus())
                    bullet[i].draw();
            }

            if (boom)
                DrawTextureRec(boomTexture, frameRect, boomPos, RAYWHITE);

            scoreText = "SCORE: " + std::to_string(score);
            DrawText(scoreText.c_str(), GetScreenWidth() / 2 - MeasureText(scoreText.c_str(), 20) / 2, 10, 20, WHITE);
            DrawText(controls1.c_str(), 1070 - MeasureText(controls1.c_str(), 20) / 2, 10, 20, GRAY);
            DrawText(controls2.c_str(), 1160 - MeasureText(controls2.c_str(), 20) / 2, 10, 20, GRAY);
            DrawText("SPACE -> Shoot", 1070 - MeasureText("SPACE -> Shoot", 20) / 2, 120, 20, GRAY);
            break;


        case GAMEOVER:
            DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 + 50, 20, WHITE);
            DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 80) / 2, 200, 80, RED);
            
            std::string scoreText = "YOUR SCORE: " + std::to_string(score);
            DrawText(scoreText.c_str(), GetScreenWidth() / 2 - MeasureText(scoreText.c_str(), 20) / 2, GetScreenHeight() / 2 - 50, 20, YELLOW);
            DrawText("PRESS [ESC] TO EXIT", GetScreenWidth()/2 - MeasureText("PRESS [ESC] TO EXIT", 20)/2, GetScreenHeight()/2 + 100, 20, WHITE);
            break;
    }
}

void Game::run() {
    while (!window.ShouldClose()) {
        update();

        BeginDrawing();
            render();
        EndDrawing();
    }
}

void Game::resetGame()
{
    score = 0;
    player.init();
    
    for (int i = 0; i < numberOfAsteroids; i++)
    {
        asteroids[i].init();
        smallAsteroids[i].init();
    }

    for (int i = 0; i < maxBullets; i++)
    {
        bullet[i].init();
    }
}