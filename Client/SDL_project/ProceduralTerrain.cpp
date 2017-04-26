#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
}


ProceduralTerrain::~ProceduralTerrain()
{
}

void ProceduralTerrain::spawnTrees(Level& level)
{
	std::cout << "Spawning Plants.." << std::endl;
	for (int i = numberOfTrees; i > 0; i--)
	{
		int x = rand() % level.grid.size();
		int y = rand() % level.grid[0].size();
		level.grid[x][y]->isTree = true;
		int treeType = rand() % 2;
		if (treeType <= 0)
			level.grid[x][y]->isOakTree = true;
		else
			level.grid[x][y]->isFernTree = true;
	}
	std::cout << numberOfTrees << " Trees spawned." << std::endl;
}

void ProceduralTerrain::spawnVegetation(Level& level)
{
	std::cout << "Spawning Plants.." << std::endl;
	for (int i = numberOfPlants; i > 0; i--)
	{
		int x = rand() % level.grid.size();
		int y = rand() % level.grid[0].size();
		level.grid[x][y]->isVegetation = true;
		int vegType = rand() % 2;
		if (vegType <= 0)
			level.grid[x][y]->isFlower1 = true;
		else
			level.grid[x][y]->isFlower2 = true;
	}
	std::cout << numberOfPlants << " Plants spawned." << std::endl;
}


void ProceduralTerrain::populateTerrain(Level& level)
{
	//generate noise from seed
	perlinNoise.GenerateNoise(SDL_GetTicks());
	for (int x = 0; x < level.grid.size() - 1; x++)
	{
		std::cout << "Loading Line : " << x << std::endl;
		for (int y = 0; y < level.grid[0].size() - 1; y++)
		{
			if (rand() % 2 <= 0)
				level.grid[x][y]->isGrass1 = true;
			else
				level.grid[x][y]->isGrass2 = true;
			level.grid[x][y]->isWalkable = true;
			double noise = perlinNoise.noise((double)x / 180.0, (double)y / 180.0, 0.0);
			//noise = (char)((noise - 0) * (255 / (noise - 0)));

			noise *= 10;

			level.grid[x][y]->noiseValue = noise;

			if (noise > 0.5)
				level.grid[x][y]->isDirt = true;

			level.grid[10][30]->isCargo = true;
			//Renders all he cells
		}
	}
	spawnTrees(level);
	spawnVegetation(level);
}