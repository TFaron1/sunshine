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

class Food
{
private: 
    int foodHp;
    int eatSpeed;
    bool isAte = false;
public:
    Food(int foodHp, int eatSpeed, bool isAte, Vector2 position)
    {
        this->foodHp = foodHp;
        this->eatSpeed = eatSpeed;
        this->isAte = isAte;
        position = GetMousePosition();
    }
    
    void Draw(Vector2 position)
    {
        DrawCircleV(position, 10, BLUE);
    }

    bool IsEating()
    {
        foodHp = 1;
        foodHp -= eatSpeed;

        if (foodHp = 0)
        {
          
            return true;
        }
        return false;
    }
   
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
        Food food(100, 10, false,GetMousePosition());
        std::vector<Food*> AllFood;

        int i = 0;

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
        //acceleration = Normalize(place - position) * 500 - velocity;
        
        if (IsKeyPressed(KEY_ZERO))
        {
            i = 0;
        }

        if (IsKeyPressed(KEY_ONE))
        {
            i = 1;
        }

        if (IsKeyPressed(KEY_TWO))
        {
            i = 2;
        }

        if (IsKeyPressed(KEY_THREE))
        {
            i = 3;
        }

        switch (mode = NONE)
        {

        case NONE:
            {
            if (i == 0)
        {
            DrawText("Mode 0: nothing", 16, 9, 20, RED);

        }
            }
     
        case SEEK:
        {
        if (i == 1)
        {
            DrawText("Mode 1: seek", 16, 9, 20, RED);
        }

        }
        case FLEE:
        {
            if (i == 2)
            {
                DrawText("Mode 2: Flee", 16, 9, 20, RED);
            }
        }

        case ARRIVE:
        {
            if (i == 3)
            {
                DrawText("Mode 3: arrive", 16, 9, 20, RED);
            }
        }

        }

           

        if (IsMouseButtonPressed(0) && food.IsEating() == false)
        {

            food.Draw(GetMousePosition());
        }
        
        

        if (IsMouseButtonDown(1))
        {
           // acceleration = Negate(Normalize(place - position) * 500 - velocity);
        }

        DrawCircleV(position, 50, RED);

       position = WrapAroundScreen(position);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}