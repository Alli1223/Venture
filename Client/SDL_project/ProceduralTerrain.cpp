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
			level.grid[x][y]->isGrass = true;
			level.grid[x][y]->isWalkable = true;
			double noise = perlinNoise.noise((double)x / 180.0, (double)y / 180.0, 0.0);
			noise = (char)((noise - 0) * (255 / (noise - 0)));
			
			level.grid[x][y]->noiseValue = noise;

			level.grid[10][30]->isCargo = true;
			//Renders all he cells
			//cellrenderer.RenderCells(level, renderer, x, y);
		}
	}
	spawnTrees(level);
}