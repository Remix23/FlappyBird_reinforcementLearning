#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "setting.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef enum GAME_STATE {
    PLAY, 
    MENU,
} GAME_STATE;

// random value generator: simulate various distribution?

// uniform 10% - 90%
float randomUnif (float min, float max) {
    return (min + (max - min) * ((float)rand() / RAND_MAX));
}

// heigth < 0.5 * scren height
void drawObstacle (float obstacleX, float obstacleHeight, float gap) {

    DrawRectangle(obstacleX, 0, OBSTACLE_WIDTH, obstacleHeight - gap / 2, RED);
    DrawRectangle(obstacleX, obstacleHeight + gap / 2, OBSTACLE_WIDTH, SCREEN_HEIGHT - obstacleHeight - gap / 2, RED);
}

void drawMenu () {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Press SPACE to start!", 200, 200, 20, LIGHTGRAY);
    EndDrawing();
}

bool checkCollision (float birdheight, Vector3 obstacles[], int numObstacles) {
    Vector2 birdPos = {100, birdheight};
    
    // check for the ground and ceiling:
    if (birdheight - BIRD_RADIUS < 0 || birdheight + BIRD_RADIUS > SCREEN_HEIGHT) {
        return true;
    }
    // obstacles
    for (int i = 0; i < numObstacles; i++) {
        float gap = obstacles[i].z;
        Rectangle recTop = {obstacles[i].x, 0, OBSTACLE_WIDTH, obstacles[i].y - gap / 2};
        Rectangle recBottom = {obstacles[i].x, obstacles[i].y + gap / 2, OBSTACLE_WIDTH, SCREEN_HEIGHT - obstacles[i].y - gap / 2};
        if (CheckCollisionCircleRec(birdPos, BIRD_RADIUS, recTop) || CheckCollisionCircleRec(birdPos, BIRD_RADIUS, recBottom)) {
            return true;
        }
    }
    return false;
}


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Reinforcement Learning");

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second

    float time = 0.0f;
    // float score = 0.0f;
    float rectangleOnScreen = 3;

    float birdHeight = GetScreenHeight()/2.0f;
    float birdVelocity = 0.0f;

    GAME_STATE gameState = MENU;

    Vector3 obstacles[5];

    float spacing = (SCREEN_WIDTH + OBSTACLE_WIDTH) / rectangleOnScreen;

    obstacles[0] = (Vector3){SCREEN_WIDTH, randomUnif(0.1, 0.9) * SCREEN_HEIGHT, 135.0};
    obstacles[1] = (Vector3){SCREEN_WIDTH - spacing, randomUnif(0.1, 0.9) * SCREEN_HEIGHT, 135.0};
    obstacles[2] = (Vector3){SCREEN_WIDTH - 2 * spacing, randomUnif(0.1, 0.9) * SCREEN_HEIGHT, 135.0};
    obstacles[3] = (Vector3){SCREEN_WIDTH - 3 * spacing, randomUnif(0.1, 0.9) * SCREEN_HEIGHT, 135.0};
    obstacles[4] = (Vector3){SCREEN_WIDTH - 4 * spacing, randomUnif(0.1, 0.9) * SCREEN_HEIGHT, 135.0};

    // Main game loop
    while (!WindowShouldClose())             // Detect window close button or ESC key
    {
        // update
        float dtime = GetFrameTime();
        if (gameState == MENU) {
            drawMenu();
            if (IsKeyDown(KEY_SPACE)){
                time = 0.0f;
                birdHeight = GetScreenHeight()/2.0f;
                birdVelocity = 0.0f;
                for (int i = 0; i < rectangleOnScreen; i++) {
                    obstacles[i].x = SCREEN_WIDTH - i * spacing;
                    obstacles[i].y = randomUnif(0.1, 0.9) * SCREEN_HEIGHT;
                    obstacles[i].z = 135.0f;
                gameState = PLAY;
                }
            }
            continue;
        }

        time += dtime;

        float speed = MIN(SPEED_MAX, SPEED_FACTOR * time + 20.0f);

        speed *= dtime;

        for (int i = 0; i < rectangleOnScreen; i++) {
            obstacles[i].x -= speed;

            if (obstacles[i].x < -OBSTACLE_WIDTH) {
                obstacles[i].x += SCREEN_WIDTH + OBSTACLE_WIDTH;
                obstacles[i].y = randomUnif(0.1, 0.9) * SCREEN_HEIGHT;
            }
        }
        birdVelocity += GRAVITY * dtime;
        if (IsKeyDown(KEY_SPACE)) {
            birdVelocity = -BIRD_JUMP_VEC;
        } 
        birdHeight += birdVelocity * dtime;

        bool collision = checkCollision(birdHeight, obstacles, rectangleOnScreen);

        if (collision) {
            gameState = MENU;
            continue;
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the bird:
        DrawCircle(100, birdHeight, BIRD_RADIUS, BLUE);

        DrawFPS(700, 15);

        for (int i = 0; i < rectangleOnScreen; i++) {
            drawObstacle(obstacles[i].x, obstacles[i].y, obstacles[i].z);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();              // Close window and OpenGL context

    return 0;
}
