#include "rlImGui.h"
#include "Math.h"
#include <vector>
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
        const float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Mode 1: food", 16, 9, 20, RED);
       
        rlImGuiBegin();
        ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
        ImGui::DragFloat2("velocity", &(velocity.x), 1, -maxSpeed, maxSpeed);
        ImGui::DragFloat2("acceleration", &(acceleration.x), 1, -maxAccel, maxAccel);
        rlImGuiEnd();

        
        Vector2 place = GetMousePosition();

        if (IsMouseButtonPressed(0))
        {
            DrawCircleV(place, 10, BLUE);
        }
        
        Vector2 displacement = velocity * dt;
        position = position + displacement + acceleration * 0.5 * dt * dt;
        velocity = velocity + acceleration * dt;
        velocity = velocity + acceleration * dt;
        acceleration = Normalize(place - position) * 500 - velocity;


        if (IsMouseButtonDown(1))
        {
            acceleration = Negate(Normalize(position - place) * 500 - velocity);
        }
        DrawCircleV(position, 50, RED);

       position = WrapAroundScreen(position);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}