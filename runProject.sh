MAIN_FILE="main.cpp"
OUTPUT_FILE="game"
SRC_FILES="src/Game.cpp src/Player.cpp src/Collisions.cpp src/BackGround.cpp src/Asteroids.cpp src/Bullet.cpp"

g++ $MAIN_FILE $SRC_FILES -o $OUTPUT_FILE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

./$OUTPUT_FILE