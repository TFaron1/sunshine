#pragma once
#include "Tilemap.h"
#include <unordered_map>

class Pathfinder
{
public:
	TileMap* map = nullptr;

private:

	std::unordered_map<TileCoord, float, std::hash<TileCoord>, std::equal_to<TileCoord>> unvisited;

	std::unordered_map<TileCoord, float, std::hash<TileCoord>, std::equal_to<TileCoord>> visited;

	std::unordered_map<TileCoord, TileCoord, std::hash<TileCoord>, std::equal_to<TileCoord>> cheapestEdgeTo;

	TileCoord startNode;
	TileCoord goalNode;
	TileCoord currentNode;

	Pathfinder()
	{

	}

	Pathfinder(TileMap* levelToNavigate, TileCoord startTile, TileCoord endTile)
	{
		map = levelToNavigate;
		startNode = startTile;
		goalNode = endTile;
		currentNode = startNode;
		Restart();
	}

	void Restart()
	{
		visited.clear();
		cheapestEdgeTo.clear();

		//reset costs
		unvisited.clear();
		for (TileCoord position : map->GetAllTraversableTiles())
		{
			unvisited[position] = INFINITY;
		}
		unvisited[startNode] = 0;
	}

	std::pair<TileCoord, float> GetLowestCostIn(std::unordered_map<TileCoord, float> set)
	{
		TileCoord cheapestPosition = { -1, -1 };
		float lowestCost = INFINITY;

		for (auto nodeValuePair : set)
		{
			TileCoord tile = nodeValuePair.first;
			float cost = nodeValuePair.second;

			if (cost < lowestCost)
			{
				cheapestPosition = tile;
				lowestCost = cost;
			}
		}
		return { cheapestPosition, lowestCost };
	}
	bool isVisited(TileCoord pos) const { return visited.count(pos); }
	bool isSolved() const { return isVisited(goalNode); }
	bool isCompleated() { return isVisited(goalNode) || GetLowestCostIn(unvisited).second == INFINITY; }

	void processNextIterationFunctional()
	{
		if (isCompleated()) return;
		currentNode = GetLowestCostIn(unvisited).first;

		moveToVisitedSet(currentNode);
	}

	void moveToVisitedSet(TileCoord node)
	{
		visited[currentNode] = unvisited[currentNode];
		unvisited.erase(currentNode);
	}

	bool solvePath()
	{
		Restart();
		while (!isCompleated())
		{
			processNextIterationFunctional();
		}

		return isCompleated();
	}
};
