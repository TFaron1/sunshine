#pragma once
#include "TileCoord.h"
#include "raylib.h"


const unsigned int  MAP_WIDTH = 24;
const unsigned int MAP_HEIGHT = 12;

enum Tile
{
	Floor = 0,
	Wall,
	Count
	
};

class TileMap
{
public:
	int tileSizeX = 32;
	int tileSizeY = 32;

	Tile tiles[MAP_WIDTH][MAP_HEIGHT];
	Color tileColors[Tile::Count];

	TileMap()
	{
		tileColors[Floor] = GRAY;
		tileColors[Wall] = ORANGE;
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

	

	void DrawTiles()
	{
		for (int x = 0; x < GetWidth(); x++)
		{
			for (int y = 0; y < GetHeight(); y++)
			{
				Tile tile = tiles[x][y];
				Vector2 position = ScreenPosOfTile({ x,y });
				Color color = WHITE;
				if (tile == Floor) color = GREEN;
				else if(tile == Wall) color = ORANGE;
				DrawRectangleV(position, { (float)tileSizeX, (float)tileSizeY }, color);
			}
		}
	}
};