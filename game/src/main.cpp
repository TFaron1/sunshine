#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    InitAudioDevice();//to get sounds to work you must include initaudiodevice
    
    float vol = 1.0f;
                             ///LOAD///
   
    Texture2D  texture = LoadTexture("../game/assets/textures/letterKenny.png");//loading image

    Sound sound = LoadSound("../game/assets/audio/chaChing.mp3");// load sound effect
    Music bgmusic = LoadMusicStream("../game/assets/audio/sweet.mp3");//load music          

    Font font = LoadFont("../game/assets/fonts/bitCheese.ttf");//laods a new font  

    Color color = BLUE;
    Color recCol = BLUE;

    Rectangle rec1;
    Rectangle  rec2;
   
        PlayMusicStream(bgmusic);//plays music 

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}