#include <raylib.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - palette switch");

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    

    Vector2 ball_pos = { (float)screenWidth/2, (float)screenHeight/2 };


    // Main game loop
    while (!WindowShouldClose())             // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_RIGHT)) ball_pos.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ball_pos.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ball_pos.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ball_pos.y += 2.0f;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ball_pos, 50, MAROON);

        DrawFPS(700, 15);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();              // Close window and OpenGL context

    return 0;
}
