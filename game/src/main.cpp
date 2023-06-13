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
    ARRIVE
};

//class Food
//{
//private: 
//    int foodHp;
//    int eatSpeed;
//    bool isAte = false;
//public:
//    Food(int foodHp, int eatSpeed, bool isAte, Vector2 position)
//    {
//        this->foodHp = foodHp;
//        this->eatSpeed = eatSpeed;
//        this->isAte = isAte;
//        position = GetMousePosition();
//    }
//    
//    void Position()
//    {
//
//    }
//
//    void Draw(Vector2 position)
//    {
//        DrawCircleV(position, 10, BLUE);
//    }
//
//    bool IsEating()
//    {
//        foodHp = 1;
//        foodHp -= eatSpeed;
//
//        if (foodHp = 0)
//        {
//          
//            return true;
//        }
//        return false;
//    }
//   
//};

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

    Mode mode;
   
    std::vector<Food> AllFood;
    std::vector<Pred> AllPred;

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
                acceleration = Normalize(GetMousePosition() - position) * 500 - velocity;
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
                if (IsMouseButtonDown(0))
                {
              //  acceleration = Negate(Normalize(GetMousePosition() - position) * 500 - velocity);
                }
            }
  
        }

        case ARRIVE:
        {
            if (key == 3)
            {
                DrawText("Mode 3: arrive", 16, 9, 20, RED);

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    Food food;
                    food.Position = GetMousePosition();
                    food.radius = 10.0;
                    // food.Draw(GetMousePosition());
                    AllFood.push_back(food);
                }
            }
    
        }

        }
     
                for (const Food& food : AllFood)
                {
                    DrawCircle(food.Position.x, food.Position.y, food.radius, BLUE);//draws food
                }
                
                for (const Pred& pred : AllPred)
                {
                    DrawCircle(pred.position.x, pred.position.y, pred.radius, RED);//draws predators
                    if (CheckCollisionCircles(pred.position, 10, position, 10))
                    {
                        acceleration = Negate(Normalize(GetMousePosition() - position) * 500 - velocity);
                     }
                }


        DrawCircleV(position, 50, BLACK);

        position = WrapAroundScreen(position);
        EndDrawing();
    }

    CloseWindow();
    return 0;

}