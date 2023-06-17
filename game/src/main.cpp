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
        {
            map.playerPosition -= TileCoord(0, 1);
        }

        if (IsKeyPressed(KEY_A) && map.IsWalkable(map.playerPosition - TileCoord(1, 0)))
        {
            map.playerPosition -= TileCoord(1, 0);
        }

        if (IsKeyPressed(KEY_S) && map.IsWalkable(map.playerPosition + TileCoord(0, 1)))
        {
            map.playerPosition += TileCoord(0, 1);
        }

        if (IsKeyPressed(KEY_D) && map.IsWalkable(map.playerPosition + TileCoord(1, 0)))
        {
            map.playerPosition += TileCoord(1, 0);
        }

		map.DrawTiles();
		
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                if (map.IsWalkable(TileCoord(x, y)))
                {
                    Vector2 center = map.GetScreenPositionOfTile(TileCoord(x, y)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };

                    int xAdjacent = 0;
                    int yAdjacent = 0;


                    xAdjacent = x + 1;
                    yAdjacent = y;
                    if (xAdjacent < MAP_WIDTH && map.IsWalkable(TileCoord(xAdjacent, yAdjacent)))
                    {
                        Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                        DrawLineEx(center, adjacentTileCenter, 1, BLACK);
                    }


                    xAdjacent = x - 1;
                    yAdjacent = y;
                    if (xAdjacent >= 0 && map.IsWalkable(TileCoord(xAdjacent, yAdjacent)))
                    {
                        Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                        DrawLineEx(center, adjacentTileCenter, 1, BLACK);
                    }

                    xAdjacent = x;
                    yAdjacent = y - 1;
                    if (yAdjacent >= 0 && map.IsWalkable(TileCoord(xAdjacent, yAdjacent)))
                    {
                        Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                        DrawLineEx(center, adjacentTileCenter, 1, BLACK);
                    }


                    xAdjacent = x;
                    yAdjacent = y + 1;
                    if (yAdjacent < MAP_HEIGHT && map.IsWalkable(TileCoord(xAdjacent, yAdjacent)))
                    {
                        Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                        DrawLineEx(center, adjacentTileCenter, 1, BLACK);
                    }

                    DrawCircle(center.x, center.y, 5, BLACK);
                }
            }
        }


        EndDrawing();
    }

    CloseWindow();
    return 0;
}