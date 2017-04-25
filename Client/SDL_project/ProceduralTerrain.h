#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "Level.h"
class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	PerlinNoise perlinNoise;

	//void ProceduralTerrain::makeGrid(int Window_Width, int Window_Height);

	void ProceduralTerrain::spawnTrees(Level& level);

	void ProceduralTerrain::populateTerrain(Level& level);

	//! The base grid that contains the cells
	//std::vector<std::vector<std::shared_ptr<Cell>>> grid;

	int numberOfTrees = 5000;

};

