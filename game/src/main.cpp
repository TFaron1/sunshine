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
       
        HideCursor();//hides the mouse on the screen allowing the cursor to take some other form

        texture.height = SCREEN_HEIGHT;
        texture.width = SCREEN_WIDTH;
        DrawTexture(texture, 0, 0,RAYWHITE);//drawing the image

        UpdateMusicStream(bgmusic);
        
        if (IsKeyPressed(KEY_P) && IsMusicStreamPlaying(bgmusic) == true) 
        {
            PauseMusicStream(bgmusic);// pauses music 
        }

        else if (IsKeyPressed(KEY_P) && IsMusicStreamPlaying(bgmusic) == false)
        {
            ResumeMusicStream(bgmusic);// resumes music
        }

        if (IsKeyPressed(KEY_EQUAL) == true)
        {
            vol += 1;
            if (vol > 4)
            {
                vol = 4;
        }
        }

        if (IsKeyPressed(KEY_MINUS) == true)
        {
            vol -= 1;
            if (vol < 0)
            {
                vol = 0;
            }
        }
        
        SetMusicVolume(bgmusic, vol);
        if (IsKeyPressed(KEY_SPACE))
        {
             PlaySound(sound);
        }

        DrawPixel(10, 10, BLACK);
        
        
        /////////////HOMEWORK PART 2////////////

         Vector2 center;
         center.x = 100;
         center.y = 100;
        
         Vector2 center2;
         center2.x = GetMouseX();
         center2.y = GetMouseY();

         if (IsMouseButtonPressed(1))
         {
             recCol.r = GetRandomValue(1, 255);
             recCol.g = GetRandomValue(1, 255);
             recCol.b = GetRandomValue(1, 255);
         }
        DrawRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, recCol);
       
             DrawCircle(center.x, center.y, 50, color);
             DrawCircle(center2.x, center2.y, 50, color);

             if (CheckCollisionCircles(center, 50, center2, 50) == true)
             {

                 color = BLACK;
             }

            else
             {
             color = BLUE;
             }


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

/*homework part 1 function calls
1.ToggleFullscreen()      allows us to change from a small window into a full screen image or vise versa 
2.LoadFont()              this function allows us to have different fonts in our games rather than just defualt
3.DrawTextEx()            this works with LoadFont() it allows us to actually use the font we had loaded previously 
4.HideCursor()            this function lets us get rid of our mouse cursor so that we have the ability to replace it with someting else 
5.LoadMusic()             this lets us load audio the same way as LoadSound does but in this case it is different as we use it for Music rather than sound effects
6.PauseMusicStream()      pauses the music that is playing
7.IsMusicStreamPlaying()  checks if music is playing and returns a boolean if yes then true if no then false
8.ResumeMusicStream()     resumes playing the music
9.SetMusicVolume()        lets the player adjsut the music to their prefrance
10.GetRandomValue()       gives a random number based on a specified min and max
*/