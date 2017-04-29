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
		if (!level.grid[x][y]->isVegetation && !level.grid[x][y]->isWater && !level.grid[x][y]->isSand)
		{
			level.grid[x][y]->isVegetation = true;
			int treeType = rand() % 2;
			if (treeType <= 0)
				level.grid[x][y]->isOakTree = true;
			else
				level.grid[x][y]->isFernTree = true;
		}
	}
	std::cout << numberOfTrees << " Trees spawned." << std::endl;
}

void ProceduralTerrain::spawnVegetation(Level& level)
{
	std::cout << "Spawning Plants.." << std::endl;
	
	int numPlants = 0;
	for (int i = numberOfPlants; i > 0; i--)
	{
		int x = rand() % level.grid.size();
		int y = rand() % level.grid[0].size();
		
		if (!level.grid[x][y]->isVegetation && !level.grid[x][y]->isWater && !level.grid[x][y]->isSand)
		{
			level.grid[x][y]->isVegetation = true;
			int vegType = rand() % 3;
			//Item item;
			switch (vegType)
			{
			case 0:
				level.grid[x][y]->isVegetation = true;
				level.grid[x][y]->isFlower1 = true;
				break;
			case 1:
				level.grid[x][y]->isVegetation = true;
				level.grid[x][y]->isBerryPlant = true;
				//item.isBerry = true;
				//level.grid[x][y]->cellItem = item;
				break;
			case 2:
				level.grid[x][y]->isVegetation = true;
				level.grid[x][y]->isFlower2 = true;
				break;
			}
			numPlants++;
		}
	}
	std::cout << numPlants << " Plants spawned." << std::endl;
}


void ProceduralTerrain::generateGrass(Level& level, int x, int y)
{
	double noise = groundNoise.noise((double)x / terrainNoiseOffest, (double)y / terrainNoiseOffest, 0.0) * 20;
	double fNoise = forrestNoise.noise((double)x / forrestNoiseOffset, (double)y / forrestNoiseOffset, 0.0) * 20;
	double pNoise = pathNoise.noise((double)x / forrestNoiseOffset, (double)y / forrestNoiseOffset, 0.0) * 20;
	double layerdNoise = noise + pNoise;
	//noise = (char)((noise - 0) * (255 / (noise - 0)));
	level.grid[x][y]->terrainNoiseValue = noise;

	//TERRAIN NOISE
	if (layerdNoise > -0.7 && layerdNoise < 13.0)
	{
		level.grid[x][y]->isGrass = true;
	}
	else if (layerdNoise > -0.5 && layerdNoise < -0.7)
	{
		level.grid[x][y]->isDirt = true;
	}
	else if (layerdNoise > -1 && layerdNoise < -0.5)
	{
		level.grid[x][y]->isSand = true;
		level.grid[x][y]->isGrass = false;
		level.grid[x][y]->isWater = false;
	}
	else
	{
		level.grid[x][y]->isWater = true;
	}

	//FORREST NOISE
	if (level.grid[x][y]->isGrass && fNoise > 10.0)
	{
		level.grid[x][y]->isVegetation = true;
		level.grid[x][y]->isFernTree = true;
	}
	else if (level.grid[x][y]->isGrass && fNoise > 5.0 && fNoise < 10.0)
	{

		level.grid[x][y]->isVegetation = true;
		level.grid[x][y]->isOakTree = true;
	}

	//PATH NOISE
	if (pNoise > 0.5 && pNoise < 1.0)
	{
		level.grid[x][y]->isDirt = true;
		level.grid[x][y]->isVegetation = false;
		level.grid[x][y]->isOakTree = false;
		level.grid[x][y]->isFernTree = false;
	}
}

void ProceduralTerrain::populateTerrain(Level& level)
{
	//generate noise from seed
	
	groundNoise.GenerateNoise(groundSeed);
	forrestNoise.GenerateNoise(forrestSeed);
	pathNoise.GenerateNoise(pathSeed);

	//Renders all he cells
	for (int x = 0; x < level.grid.size(); x++)
	{
		std::cout << "Generating Terrain: " << x << " OF " << level.grid.size() << std::endl;
		for (int y = 0 ; y < level.grid[0].size(); y++)
		{
			//Spawn the grass
			level.grid[x][y]->isWalkable = true;
			
			level.grid[10][30]->isRoom = true;
			
			//Generate the grass
			generateGrass(level, x, y);
			
		}
	}
	spawnTrees(level);
	spawnVegetation(level);
}