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

    Vector2 center = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };

    
    Vector2 position = { 100, 100 };//px
    Vector2 velocity = { 10, 0 };//px/s
    Vector2 acceleration = { 0, 50 };//px/s/s
    float maxSpeed = 1000;
    float maxAccel = 1000;
   // Vector2 toTarget = {position2.x - position.x,position2.y - position.y};
   

    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();
        
        HideCursor();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        
        rlImGuiBegin();// to make any imgui window appear call rlImGuiBegin
        ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
        ImGui::DragFloat2("velocity", &(velocity.x),1,-maxSpeed, maxSpeed);
        ImGui::DragFloat2("acceleration", &(acceleration.x),1,-maxAccel,maxAccel);
        rlImGuiEnd();// end with this when making imgui windows appear
        Vector2 position2 = GetMousePosition();
        //update kinematics sim

        Vector2 displacement = velocity * dt;//px/s * s= px
        position = position + displacement + acceleration * 0.5 * dt * dt;
        velocity = velocity + acceleration * dt;//px/s + (px/s/s * s)
        acceleration = Normalize(position2 - position) * 500 - velocity;
       
        if (IsKeyDown(KEY_A))//flee
        {
            acceleration = Negate(Normalize(position2 - position) * 500 - velocity);
            
        }
        
   

        //draw circle and lines showing velocity and acceleration
        DrawCircleV(center, 100, RAYWHITE);//flee radius
        DrawCircleV(center, 50, PINK);//center circle
        DrawCircleV(position, 50, BLUE);//seek circle
        DrawCircleV(position2, 50, BLACK);//mouse cicle

        DrawLineV(position, position + velocity, RED);
        DrawLineV(position, position + acceleration, GREEN);
        DrawLineV(position, position + (position2 - position) * 150, BLACK);
     
       if(CheckCollisionCircles(center, 100, position, 50) == true)//if the circle reaches a radius close to the center cicle if will call flee
        {
           acceleration = Negate(Normalize(center - position) * 500 - velocity);
        }
        
        
       

        position = WrapAroundScreen(position);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}