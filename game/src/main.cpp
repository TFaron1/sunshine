#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);
    rlImGuiSetup(true);

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