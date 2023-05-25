#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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
        const float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        
        rlImGuiBegin();
        ImGui::DragFloat2("position", &(position.x), 0, SCREEN_WIDTH);
        ImGui::DragFloat2("velocity", &(velocity.x),1,-maxSpeed, maxSpeed);
        ImGui::DragFloat2("acceleration", &(acceleration.x),1,-maxAccel,maxAccel);
        rlImGuiEnd();

        Vector2 displacement = velocity * dt;
        position = position + displacement;
        velocity = velocity + acceleration * dt;

        DrawCircleV(position, 50, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}