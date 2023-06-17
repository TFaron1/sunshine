#pragma once
#include "TileCoord.h"
#include "raylib.h"
#include <vector>

const unsigned int  MAP_WIDTH = 24;
const unsigned int MAP_HEIGHT = 12;

const Vector2 NORTH = { -1, 0 };
const Vector2 SOUTH = { 1, 0 };
const Vector2 EAST = { 0,  1 };
const Vector2 WEST = { 0, -1 };

enum class Tile
{
	Floor = 0,
	Wall,
	Count,
	Player
	
};

class TileMap
{
private:
	bool isWalkable[(int)Tile::Count];

public:
	float tileSizeX = 32;
	float tileSizeY = 32;


	Tile tiles[MAP_WIDTH][MAP_HEIGHT];
	Color tileColors[(int)Tile::Count];

	TileCoord playerPosition;

	Tile GetTile(int x, int y);


	Vector2 GetScreenPositionOfTile(TileCoord tilePosition)
	{
		return { tilePosition.x * tileSizeX,tilePosition.y * tileSizeY };

	}

	Vector2 GetTileAtScreenPosition(Vector2 tilePosition)
	{
		return { tilePosition.x / tileSizeX, tilePosition.y / tileSizeY };
	}

	TileMap()
	{
		tileColors[(int)Tile::Floor] = GRAY;
		tileColors[(int)Tile::Wall] = ORANGE;

		isWalkable[(int)Tile::Floor] = true;
	}


	bool IsWalkable(TileCoord tilePosition)
	{
		if (tilePosition.x >= 0 && tilePosition.x < MAP_WIDTH && tilePosition.y >= 0 && tilePosition.y < MAP_HEIGHT)
		{
			Tile type = tiles[tilePosition.x][tilePosition.y];
			return isWalkable[static_cast<int>(type)];
		}
		return false;
	}


	Vector2 ScreenPosOfTile(TileCoord tilePosition)
	{
		return { (float)tilePosition.x * tileSizeX, (float)tilePosition.y * tileSizeY };
	}

	unsigned int GetWidth()
	{
		return MAP_WIDTH;
	}


	unsigned int GetHeight()
	{
		return MAP_HEIGHT;
	}

	void RandomTiles(TileMap& level, float chanceOfWall = 0.2)
	{
		for (int x = 0; x < level.GetWidth(); x++)
		{
			for (int y = 0; y < level.GetHeight(); y++)
			{


				if (GetRandomValue(0.0, 1.0) < chanceOfWall)
				{
					level.tiles[x][y] = Tile::Wall;
				}
				else
				{
					level.tiles[x][y] = Tile::Floor;
				}
			}//Randomize the player spawn
			int playerX;
			int playerY;

			do
			{
				playerY = rand() % MAP_HEIGHT;
				playerX = rand() % MAP_WIDTH;
			} while (tiles[playerX][playerY] != Tile::Floor);
			playerPosition = TileCoord(playerX, playerY);
		}
	}

	std::vector<Vector2> GetWalkableAdjacentTo(Vector2 tilePos)
	{
		std::vector<Vector2> adjacentTilePosition;

		Vector2 N = tilePos + NORTH;
		Vector2 S = tilePos + SOUTH;
		Vector2 E = tilePos + EAST;
		Vector2 W = tilePos + WEST;

		if(IsWalkable(N)) adjacentTilePosition.push_back(N);
		if(IsWalkable(S)) adjacentTilePosition.push_back(S);
		if(IsWalkable(E)) adjacentTilePosition.push_back(E);
		if(IsWalkable(W)) adjacentTilePosition.push_back(W);

		return adjacentTilePosition;
	}


	void DrawTiles()
	{
		for (int x = 0; x < GetWidth(); x++)
		{
			for (int y = 0; y < GetHeight(); y++)
			{
				Tile tile = tiles[x][y];
				Vector2 position = ScreenPosOfTile({ x,y });
				Color color = WHITE;
				if (tile == Tile::Floor) color = GREEN;
				else if(tile == Tile::Wall) color = ORANGE;
			DrawRectangleV(position, { (float)tileSizeX, (float)tileSizeY }, color);

				Vector2 playerPositionScreen = GetScreenPositionOfTile(playerPosition);
			DrawRectangle(static_cast<int>(playerPositionScreen.x), static_cast<int>(playerPositionScreen.y), tileSizeX, tileSizeY, BLACK);
				
			}
		}
	}
};