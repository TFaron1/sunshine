#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 WraparoundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        fmodf(position.x + SCREEN_WIDTH , SCREEN_WIDTH),
        fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };

    return outPosition;
}


class Rigidbody
{
public:
    Vector2 position;
    Vector2 velocity;
};

// Sprite class
class Sprite
{
public:
    Texture2D texture;
    Vector2 position;
    Rectangle bounds;

    void Draw()
    {
        DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
    }
};

// Agent class
class Agent
{
public:
    Rigidbody rigidbody;
    Sprite sprite;
    float maxSpeed;
    float maxAcceleration;
};

//Vector2 flee(const Vector2& agentPosition, const Vector2& agentVelocity, const Vector2& targetPosition, float maxAcceleration)
//{
//    Vector2 desiredVelocity = Normalize(agentPosition - targetPosition) * maxAcceleration;
//    Vector2 steer = desiredVelocity - agentVelocity;
//    return steer;
//}


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(144);

    rlImGuiSetup(true); // Sets up imgui

    Vector2 position{ 100,100 };
    Vector2 targetPosition;
    Vector2 velocity = { 10.0, 0.0 };
    Vector2 acceleration = { 10.0f, 0.0f };
    //Vector2 displacementPositionTarget = position- targetPosition;
    float speed = 500;
    float maxSpeed = 1000;
    float maxAccel = 1000;
    bool useGUI = false;
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();

            ImGui::DragFloat2("Position", &(position.x), 0, SCREEN_WIDTH);
            ImGui::DragFloat2("Velocity", &(velocity.x), -maxSpeed, maxSpeed);
            ImGui::DragFloat2("Acceleration", &(acceleration.x), 1, -maxAccel, maxAccel);

            rlImGuiEnd();
        }

        targetPosition = GetMousePosition();
        HideCursor();



        //Vector2 displacement = velocity * deltaTime;
        //position = position + displacement;

        //Vector2 deltaV = acceleration * deltaTime;
        //velocity = velocity + deltaV;




        Vector2 agentToTarget = targetPosition - position;

        Vector2 directionToTarget = Normalize(agentToTarget);


        acceleration = directionToTarget *maxAccel; 




            position = position + velocity* deltaTime + acceleration * deltaTime * deltaTime * 0.5f;
        velocity = velocity + acceleration * deltaTime;

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            acceleration = Normalize(targetPosition - position) * speed - velocity;
        }
        else
        {
            acceleration = Normalize(position - targetPosition) * speed - velocity;
        }




        //acceleration = { 0,0 };
        position = WraparoundScreen(position);




        DrawText("Hello World!", 16, 9, 20, RED);

        DrawCircleV(position, 50, BLUE);
        DrawCircleGradient(targetPosition.x, targetPosition.y, 50, LIGHTGRAY, BLACK);

        DrawLineV(position, position + velocity, RED);
        DrawLineV(position, position + acceleration, GREEN);
        DrawLineV(position, position + (targetPosition - position) * 150, ORANGE);



        DrawFPS(1200, 10);

        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}