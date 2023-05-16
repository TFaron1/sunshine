#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

    
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    Texture2D  texture = LoadTexture("../game/assets/textures/letterKenny.png");//loading image using the path
   Sound sound = LoadSound("../game/assets/audio/laser.mp3");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
       
        texture.height = SCREEN_HEIGHT;
        texture.width = SCREEN_WIDTH;
        DrawTexture(texture, 0, 0,RAYWHITE);//drawing the image

        if (IsKeyPressed(32))
        {
        PlaySound(sound);

        }

        DrawPixel(10, 10, BLACK);
        

        DrawCircle(100, 100, 50, BLUE);
        DrawRectangle(500, 500, 50, 50, RED);
        DrawLine(200, 200, 400, 200, YELLOW);
        DrawRectangle(GetMouseX(), GetMouseY(), 100, 100,WHITE);//this will draw a rectangle at the position of the mouse useing GetMouseX and GetMouseY functions 


       if( IsKeyPressed(49))  //this checks is if key 49 or "1" on the ascii table is presed if so it changes is key presseed to true allow the user to use keyboard inputs 
        {
        ToggleFullscreen();//This function changes the screen from small to filling the users entire screen this is good because the player will view only the game and not be distracted by backgrounds and such
        }//* NOTE TO SELF: NEVER PUT TOGGLE FULLSCREEN IN A WHILE LOOP*
    }

    CloseWindow();
    return 0;
}