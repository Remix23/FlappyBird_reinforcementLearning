#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "setting.h"


#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

}

void checkCollision (float birdheight, Vector3 obstacles[], int numObstacles) {
    for (int i = 0; i < numObstacles; i++) {
        // check
        
    }

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

    Vector3 obstacles[5];

    float spacing = (SCREEN_WIDTH + OBSTACLE_WIDTH) / rectangleOnScreen;

    obstacles[0] = (Vector3){SCREEN_WIDTH, randomUnif(0.2, 0.8) * SCREEN_HEIGHT, 120.0};
    obstacles[1] = (Vector3){SCREEN_WIDTH - spacing, randomUnif(0.2, 0.8) * SCREEN_HEIGHT, 120.0};
    obstacles[2] = (Vector3){SCREEN_WIDTH - 2 * spacing, randomUnif(0.2, 0.8) * SCREEN_HEIGHT, 120.0};
    obstacles[3] = (Vector3){SCREEN_WIDTH - 3 * spacing, randomUnif(0.2, 0.8) * SCREEN_HEIGHT, 120.0};
    obstacles[4] = (Vector3){SCREEN_WIDTH - 4 * spacing, randomUnif(0.2, 0.8) * SCREEN_HEIGHT, 120.0};

    // Main game loop
    while (!WindowShouldClose())             // Detect window close button or ESC key
    {
        // update
        float dtime = GetFrameTime();

        time += dtime;

        float speed = MIN(SPEED_MAX, SPEED_FACTOR * time + 20.0f);

        speed *= dtime;

        for (int i = 0; i < rectangleOnScreen; i++) {
            obstacles[i].x -= speed;

            if (obstacles[i].x < -OBSTACLE_WIDTH) {
                obstacles[i].x += SCREEN_WIDTH + OBSTACLE_WIDTH;
                obstacles[i].y = randomUnif(0.2, 0.8) * SCREEN_HEIGHT;
            }
        }
        if (IsKeyDown(KEY_SPACE)) {
            birdVelocity = -5.0f;
        }
        birdVelocity += GRAVITY * dtime;


        birdHeight += birdVelocity;

        

        BeginDrawing();

        ClearBackground(RAYWHITE);

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
