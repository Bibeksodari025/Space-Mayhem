@echo off
setlocal

REM Set the main file, output file, and source files
set MAIN_FILE=main.cpp
set OUTPUT_FILE=game.exe
set SRC_FILES=src\Game.cpp src\Player.cpp src\Collisions.cpp src\BackGround.cpp src\Asteroids.cpp src\Bullet.cpp

REM Compile the program with MinGW
g++ %MAIN_FILE% %SRC_FILES% -o %OUTPUT_FILE% -lraylib -lopengl32 -lgdi32 -lwinmm

REM Run the executable
%OUTPUT_FILE%

endlocal

