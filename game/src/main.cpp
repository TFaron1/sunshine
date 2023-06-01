#include "rlImGui.h"
#include "Math.h"
#include<vector>
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


class Ridgidbody
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 mousePosition;
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
    Ridgidbody ridgidbody;
    Sprite sprite;
    float maxSpeed;
    float maxAcceleration;
};



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(144);
    bool collision = false;
    std::vector<Agent> agents;
    Agent agent;
    agent.ridgidbody.position = { 400, 225 };
    agent.ridgidbody.velocity = { 10, 0 };
    agent.maxSpeed = 400.0f;
    agent.maxAcceleration = 800.0f;
    Ridgidbody circleA = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
    rlImGuiSetup(true); // Sets up imgui
    Ridgidbody ridgidbody;
    ridgidbody.mousePosition = GetMousePosition();

    Vector2 acceleration = { 10.0f, 0.0f };
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

            ImGui::DragFloat2("Position", &(ridgidbody.position.x), 0, SCREEN_WIDTH);
            ImGui::DragFloat2("Velocity", &(agent.ridgidbody.velocity.x), -maxSpeed, maxSpeed);
            ImGui::DragFloat2("Acceleration", &(acceleration.x), 1, -maxAccel, maxAccel);

            rlImGuiEnd();
        }

        ridgidbody.mousePosition = GetMousePosition();
        HideCursor();

        ridgidbody.position = ridgidbody.position + agent.ridgidbody.velocity * deltaTime + acceleration * deltaTime * deltaTime * 0.5f;
        agent.ridgidbody.velocity = agent.ridgidbody.velocity + acceleration * deltaTime;

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            acceleration = Normalize(ridgidbody.mousePosition - ridgidbody.position) * speed - agent.ridgidbody.velocity;
        }
        else
        {
            acceleration = Normalize(ridgidbody.position - ridgidbody.mousePosition) * speed - agent.ridgidbody.velocity;
        }

        if (CheckCollisionCircles(circleA.position, 65, ridgidbody.position, 65))
        {
            acceleration = Normalize(ridgidbody.position - circleA.position) * speed - agent.ridgidbody.velocity;
        }


        ridgidbody.position = WraparoundScreen(ridgidbody.position);


        DrawCircleV(ridgidbody.position, 50, BLUE);
        DrawCircleV(circleA.position, 50, RED);
        DrawCircleGradient(ridgidbody.mousePosition.x, ridgidbody.mousePosition.y, 50, LIGHTGRAY, BLACK);



        DrawLineV(ridgidbody.position, ridgidbody.position + agent.ridgidbody.velocity, RED);
        DrawLineV(ridgidbody.position, ridgidbody.position + acceleration, GREEN);
        DrawLineV(ridgidbody.position, ridgidbody.position + (ridgidbody.mousePosition - ridgidbody.position) * 150, ORANGE);





        DrawText("Hello World!", 16, 9, 20, RED);
        DrawFPS(1200, 10);

        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}