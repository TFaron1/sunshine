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
		
        if (IsKeyPressed(KEY_W) && map.IsWalkable(map.playerPosition - TileCoord(0, 1)))
            map.playerPosition -= TileCoord(0, 1);
        if (IsKeyPressed(KEY_A) && map.IsWalkable(map.playerPosition - TileCoord(1, 0)))
            map.playerPosition -= TileCoord(1, 0);
        if (IsKeyPressed(KEY_S) && map.IsWalkable(map.playerPosition + TileCoord(0, 1)))
            map.playerPosition += TileCoord(0, 1);
        if (IsKeyPressed(KEY_D) && map.IsWalkable(map.playerPosition + TileCoord(1, 0)))
            map.playerPosition += TileCoord(1, 0);

		map.DrawTiles();
		

        EndDrawing();
    }

    CloseWindow();
    return 0;
}