#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
        void DrawPixel(int posx, int posy, Color color);
        DrawCircle(100, 100, 50, BLUE);
        DrawRectangle(500, 500, 50, 50, RED);
        DrawLine(200, 200, 400, 200, YELLOW);
    }

    CloseWindow();
    return 0;
}