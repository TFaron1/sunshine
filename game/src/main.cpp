#include "rlImGui.h"
#include "TileMap.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
float generateWallChance = 0.2;

TileMap map;

void RandomTiles(TileMap& level, float chanceOfWall = 0.2)
{
	for (int x = 0; x < level.GetWidth(); x++)
	{
		for (int y = 0; y < level.GetHeight(); y++)
		{


			if (GetRandomValue(0.0, 1.0)  < chanceOfWall)
			{
				level.tiles[x][y] = Wall;
			}
			else 
			{
				level.tiles[x][y] = Floor;
			}
		}
	}
}

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

		ImGui::SliderFloat("wall chance", &(generateWallChance), 0, 0.2);

		if(ImGui::Button("Randomize map"))
		{
			RandomTiles(map, generateWallChance);

		}


		rlImGuiEnd();
		
		map.DrawTiles();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}