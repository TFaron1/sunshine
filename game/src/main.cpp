#include "rlImGui.h"
#include "TileMap.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
float generateWallChance = 0.2;

TileMap map;



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);
	rlImGuiSetup(true);


	

    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);

		rlImGuiBegin();

		ImGui::SliderFloat("wall chance", &(generateWallChance), 0, 0.2f);

		if(ImGui::Button("Randomize map"))
		{
			map.RandomTiles(map, generateWallChance);

		}


		rlImGuiEnd();
		
		map.DrawTiles();
		

        EndDrawing();
    }

    CloseWindow();
    return 0;
}