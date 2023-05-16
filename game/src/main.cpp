#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    InitAudioDevice();
    


    Texture2D  texture = LoadTexture("../game/assets/textures/letterKenny.png");//loading image

    Sound sound = LoadSound("../game/assets/audio/chaChing.mp3");// load sound effect
    Music bgmusic = LoadMusicStream("../game/assets/audio/sweet.mp3");//load music          6

    Font font = LoadFont("../game/assets/fonts/bitCheese.ttf");//laods a new font   1

    Color color;

    Rectangle rec1;
    Rectangle  rec2;
   
        PlayMusicStream(bgmusic);//plays music 

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
       
        texture.height = SCREEN_HEIGHT;
        texture.width = SCREEN_WIDTH;
        DrawTexture(texture, 0, 0,RAYWHITE);//drawing the image

        UpdateMusicStream(bgmusic);
        

        if (IsKeyPressed(32))
        {
        PlaySound(sound);
        }

        DrawPixel(10, 10, BLACK);
        
        HideCursor();

        rec1.x = GetMouseX() - 10;//getmouse.x and getmouse.y returns the mouse x and y positions   2
        rec1.y = GetMouseY() - 10;
        rec1.width = 20;
        rec1.height = 20;
       
        rec2.x = 300;
        rec2.y = 300;
        rec2.width = 50;
        rec2.height = 50;
             
         DrawRectangle(rec1.x, rec1.y,rec1.width, rec1.height,WHITE);
       
         if (CheckCollisionRecs(rec1, rec2) == true)//this checks collision between rec 1 and rec 2 and shows it worked by changing the color of rec2   3         
         {

             color = BLACK;
         }

         else
         {
             color = BLUE;
         }

        DrawCircle(100, 300, 50, color);
        DrawRectangle(rec2.x, rec2.y, rec2.width, rec2.height, color);
        
     

        DrawRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, BLACK);
        Vector2 vec1;
        vec1.x = 500;
        vec1.y = 600;
        DrawTextEx(font, "Hello", vec1, 50.0, 10, BLACK);//allows us to use the previously loaded font  4

       if( IsKeyPressed(49))  //this checks is if key 49 or "1" on the ascii table is presed if so it changes is key presseed to true allow the user to use keyboard inputs         5
        {
        ToggleFullscreen();//This function changes the screen from small to filling the users entire screen this is good because the player will view only the game and not be distracted by backgrounds and such   6
        }//* NOTE TO SELF: NEVER PUT TOGGLE FULLSCREEN IN A WHILE LOOP*
    }

    CloseWindow();
    return 0;
}