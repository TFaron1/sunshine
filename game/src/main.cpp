#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 WrapAroundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        fmodf(position.x + SCREEN_WIDTH,SCREEN_WIDTH),
        fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };
    return outPosition;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    Vector2 position = { 100, 100 };//px
    Vector2 velocity = { 10, 0 };//px/s
    Vector2 acceleration = { 0, 50 };//px/s/s
    float maxSpeed = 1000;
    float maxAccel = 1000;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
       
        rlImGuiBegin();
       
        rlImGuiEnd();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}