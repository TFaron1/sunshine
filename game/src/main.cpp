#include "rlImGui.h"
#include "Math.h"
#include <vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum Mode
{
    NONE,
    SEEK,
    FLEE,
    ARRIVE,
    ObstacleAvoid
};


bool CheckCollisionLineCircle(Vector2 lineStart, Vector2 lineEnd, Vector2 circlePosition, float circleRadius)
{
    Vector2 nearest = NearestPoint(lineStart, lineEnd, circlePosition);
    return DistanceSqr(nearest, circlePosition) <= circleRadius * circleRadius;
}

struct Food
{
    Vector2 Position;
    float radius;
};  

struct Pred
{
    Vector2 position;
    float radius;
};

struct Obstacle
{
    Vector2 Position;
    float radius;
};


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

    float speed = 500;
    float maxSpeed = 1000;
    float maxAccel = 1000;

    Color lineColor = GREEN;

    Mode mode;

    std::vector<Food> AllFood;
    std::vector<Pred> AllPred;
    std::vector<Obstacle> AllObstacle;

    int key = 0;

    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlImGuiBegin();
        ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
        ImGui::DragFloat2("velocity", &(velocity.x), 1, -maxSpeed, maxSpeed);
        ImGui::DragFloat2("acceleration", &(acceleration.x), 1, -maxAccel, maxAccel);
        rlImGuiEnd();

        Vector2 displacement = velocity * dt;
        position = position + displacement + acceleration * 0.5 * dt * dt;
        velocity = velocity + acceleration * dt;
        velocity = velocity + acceleration * dt;

        if (IsKeyPressed(KEY_ZERO))
        {
            key = 0;
        }

        if (IsKeyPressed(KEY_ONE))
        {
            key = 1;
        }

        if (IsKeyPressed(KEY_TWO))
        {
            key = 2;
        }

        if (IsKeyPressed(KEY_THREE))
        {
            key = 3;
        }

        if (IsKeyPressed(KEY_FOUR))
        {
            key = 4;
        }

        switch (mode = NONE)
        {

        case NONE:
        {
            if (key == 0)
            {
                DrawText("Mode 0: nothing", 16, 9, 20, RED);

            }

        }

        case SEEK:
        {
            if (key == 1)
            {
                DrawText("Mode 1: seek", 16, 9, 20, RED);

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    acceleration = Normalize(GetMousePosition() - position) * speed - velocity;
                }
            }

        }
        case FLEE:
        {
            if (key == 2)
            {
                DrawText("Mode 2: Flee", 16, 9, 20, RED);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    Pred pred;
                    pred.position = GetMousePosition();
                    pred.radius = 10.0;
                    AllPred.push_back(pred);
                }

            }

        }

        case ARRIVE:
        {
            if (key == 3)
            {
                DrawText("Mode 3: arrive", 16, 9, 20, RED);

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    Food food;
                    food.Position = GetMousePosition();
                    food.radius = 10.0;
                    AllFood.push_back(food);
                }
            }

        }
        case ObstacleAvoid:
        {
            if (key == 4)
            {
                DrawText("Mode 4: obstacle", 16, 9, 20, RED);
               
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    Obstacle obstacle;
                    obstacle.Position = GetMousePosition();
                    obstacle.radius = 10.0;
                    AllObstacle.push_back(obstacle);
                }
            }
        }

        }
        Vector2 Whisker1 = Normalize(Vector2{ 1, -1 });
        Vector2 Whisker2 = Rotate(Whisker1, -30 * DEG2RAD);

        for (const Food& food : AllFood)
        {
            DrawCircle(food.Position.x, food.Position.y, food.radius, BLUE);//draws food
            
            if (CheckCollisionCircles(food.Position, 10, position, 50))
            {
              
            }
        }

        for (const Pred& pred : AllPred)
        {
            DrawCircle(pred.position.x, pred.position.y, pred.radius, RED);//draws predators

            if (CheckCollisionCircles(position,50,pred.position,20))
            {
                acceleration = Negate(Normalize(pred.position - position) * speed - velocity);
            }
        }

        for (const Obstacle& obstacle : AllObstacle)
        {
            DrawCircle(obstacle.Position.x, obstacle.Position.y, obstacle.radius, GRAY);//draws obstacles

            if (CheckCollisionLineCircle(position, position + Whisker1 * 100, obstacle.Position, 10) == true ||
                CheckCollisionLineCircle(position, position + Whisker2 * 100, obstacle.Position, 10) == true)
            {

                acceleration = Negate(Normalize(obstacle.Position - position) * speed - velocity);
                lineColor = RED;

            }
            else
            {

                lineColor = GREEN;
            }
          
        }
       
        if (IsKeyPressed(KEY_SPACE))
        {//removes all obstacles, food and predators
            AllObstacle.clear();
            AllFood.clear();
            AllPred.clear();
        }
        DrawCircleV(position, 50, BLACK);


        DrawLineV(position, position + Whisker1 * 100, lineColor);
        DrawLineV(position, position + Whisker2 * 100, lineColor);

        position = WrapAroundScreen(position);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;

}