#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
}


ProceduralTerrain::~ProceduralTerrain()
{
}
// Places a building in the specified area
void PlaceBuilding(Level& level, int x, int y, int sizeX, int sizeY)
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++);
		{
			level.grid[x][y]->isBuilding = true;
			level.grid[x][y]->isStoneWall = true;
		}
	}
}

void ProceduralTerrain::GenerateTerrain(Level& level, AgentManager& agentManager)
{
	if (agentManager.allAgents[0].getCellX() > level.grid.size() / 2)
	{
		//level.makeOrExtendGrid(level.getLevelWidth(), level.getLevelHeight(), generateTerrainXPos, generateTerrainYPos);
		//generateTerrainXPos += level.getLevelWidth();
		//generateTerrainYPos += 200;
	}
}

// Clears the ground and spawns buildings in the area
void ProceduralTerrain::SpawnTown(Level& level)
{
	if (numOfTowns >= 1)
	{
		bool townFound = false;
		numOfTowns--;
		while (!townFound)
		{
			int x = rand() % level.grid.size();
			int y = rand() % level.grid[0].size();
			if (level.grid[x][y]->terrainNoiseValue > 3)
			{
				
				for (int tX = x; tX < townSize + x; tX++)
				{
					for (int tY = y; tY < townSize + y; tY++)
					{

						// Clear the ground
						level.grid[tX][tY]->isGrass = true;
						level.grid[tX][tY]->isSand = false;
						level.grid[tX][tY]->isVegetation = false;
						level.grid[tX][tY]->isWater = false;
						level.grid[tX][tY]->isTown = true;

						//Place walls around
						if(!level.grid[tX][townSize + y]->isDirt)
							level.grid[tX][townSize + y]->isStoneWall = true;
						if (!level.grid[x + townSize][tY]->isDirt)
							level.grid[x + townSize][tY]->isStoneWall = true;
						if(!level.grid[x][tY]->isDirt)
							level.grid[x][tY]->isStoneWall = true;
						if(!level.grid[tX][y]->isDirt)
							level.grid[tX][y]->isStoneWall = true;
					}
				}
				townFound = true;
				PlaceBuilding(level, x, y, 5, 5);
			}
		}
	}
}




void ProceduralTerrain::spawnTrees(Level& level)
{
	std::cout << "Spawning Plants.." << std::endl;
	for (int i = numberOfTrees; i > 0; i--)
	{
		int x = rand() % level.grid.size();
		int y = rand() % level.grid[0].size();
		if (!level.grid[x][y]->isVegetation && !level.grid[x][y]->isWater && !level.grid[x][y]->isSand && !level.grid[x][y]->isTown)
		{
			level.grid[x][y]->isVegetation = true;
			int treeType = rand() % 3;
			if (treeType <= 0)
				level.grid[x][y]->isFernTree = true;
			else
				level.grid[x][y]->isOakTree = true;
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
	double layerdNoise = noise;
	//noise = (char)((noise - 0) * (255 / (noise - 0)));
	level.grid[x][y]->terrainNoiseValue = noise;

	// TERRAIN NOISE
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

	// FORREST NOISE
	if (level.grid[x][y]->isGrass && fNoise > 14.0)
	{
		level.grid[x][y]->isVegetation = true;
		level.grid[x][y]->isOakTree = true;
	}
	else if (level.grid[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0)
	{

		level.grid[x][y]->isVegetation = true;
		level.grid[x][y]->isFernTree = true;
	}

	// PATH NOISE
	if (pNoise > 0.5 && pNoise < 0.8)
	{
		level.grid[x][y]->isDirt = true;
		level.grid[x][y]->isVegetation = false;
		level.grid[x][y]->isOakTree = false;
		level.grid[x][y]->isFernTree = false;
	}
	else if (pNoise >= 1.0 && pNoise < 1.2)
	{
		level.grid[x][y]->isFernTree = true;
		level.grid[x][y]->isGrass = true;
	}
	else if (pNoise >= 1.2 && pNoise < 1.4 || pNoise >= 0.3 && pNoise < 1.0)
	{
		level.grid[x][y]->isFernTree = true;
		level.grid[x][y]->isGrass = true;
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
	SpawnTown(level);
	spawnTrees(level);
	spawnVegetation(level);
}