#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
}


ProceduralTerrain::~ProceduralTerrain()
{
}
/* Places a building in the specified area
void PlaceBuilding(Chunk& chunk, int x, int y, int sizeX, int sizeY)
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++);
		{
			chunk.tiles[x][y]->isBuilding = true;
			chunk.tiles[x][y]->isStoneWall = true;
		}
	}
}

void ProceduralTerrain::GenerateTerrain(Chunk& chunk, AgentManager& agentManager)
{
	if (agentManager.allAgents[0].getCellX() > chunk.tiles.size() / 2)
	{
		//chunk.makeOrExtendGrid(chunk.getLevelWidth(), chunk.getLevelHeight(), generateTerrainXPos, generateTerrainYPos);
		//generateTerrainXPos += chunk.getLevelWidth();
		//generateTerrainYPos += 200;
	}
}
*/
// Clears the ground and spawns buildings in the area
void ProceduralTerrain::SpawnTown(Chunk& level)
{
	if (numOfTowns >= 1)
	{
		bool townFound = false;
		numOfTowns--;
		while (!townFound)
		{
			int x = rand() % level.tiles.size();
			int y = rand() % level.tiles[0].size();
			if (level.tiles[x][y]->terrainElevationValue > 3)
			{
				
				for (int tX = x; tX < townSize + x; tX++)
				{
					for (int tY = y; tY < townSize + y; tY++)
					{

						// Clear the ground
						level.tiles[tX][tY]->isGrass = true;
						level.tiles[tX][tY]->isSand = false;
						level.tiles[tX][tY]->isVegetation = false;
						level.tiles[tX][tY]->isWater = false;
						level.tiles[tX][tY]->isTown = true;

						//Place walls around
						if(!level.tiles[tX][townSize + y]->isDirt)
							level.tiles[tX][townSize + y]->isStoneWall = true;
						if (!level.tiles[x + townSize][tY]->isDirt)
							level.tiles[x + townSize][tY]->isStoneWall = true;
						if(!level.tiles[x][tY]->isDirt)
							level.tiles[x][tY]->isStoneWall = true;
						if(!level.tiles[tX][y]->isDirt)
							level.tiles[tX][y]->isStoneWall = true;
					}
				}
				townFound = true;
				//PlaceBuilding(chunk, x, y, 5, 5);
			}
		}
	}
}




void ProceduralTerrain::spawnTrees(Chunk& level)
{
	std::cout << "Spawning Plants.." << std::endl;
	for (int i = numberOfTrees; i > 0; i--)
	{
		int x = rand() % level.tiles.size();
		int y = rand() % level.tiles[0].size();
		if (!level.tiles[x][y]->isVegetation && !level.tiles[x][y]->isWater && !level.tiles[x][y]->isSand && !level.tiles[x][y]->isTown)
		{
			level.tiles[x][y]->isVegetation = true;
			int treeType = rand() % 3;
			if (treeType <= 0)
				level.tiles[x][y]->isFernTree = true;
			else
				level.tiles[x][y]->isOakTree = true;
		}
	}
	std::cout << numberOfTrees << " Trees spawned." << std::endl;
}

void ProceduralTerrain::spawnVegetation(Chunk& level)
{
	std::cout << "Spawning Plants.." << std::endl;
	
	int numPlants = 0;
	for (int i = numberOfPlants; i > 0; i--)
	{
		int x = rand() % level.tiles.size();
		int y = rand() % level.tiles[0].size();
		
		if (!level.tiles[x][y]->isVegetation && !level.tiles[x][y]->isWater && !level.tiles[x][y]->isSand)
		{
			level.tiles[x][y]->isVegetation = true;
			int vegType = rand() % 3;
			//Item item;
			switch (vegType)
			{
			case 0:
				level.tiles[x][y]->isVegetation = true;
				level.tiles[x][y]->isFlower1 = true;
				break;
			case 1:
				level.tiles[x][y]->isVegetation = true;
				level.tiles[x][y]->isBerryPlant = true;
				//item.isBerry = true;
				//chunk.grid[x][y]->cellItem = item;
				break;
			case 2:
				level.tiles[x][y]->isVegetation = true;
				level.tiles[x][y]->isFlower2 = true;
				break;
			}
			numPlants++;
		}
	}
	std::cout << numPlants << " Plants spawned." << std::endl;
}


void ProceduralTerrain::populateTerrain(Chunk& chunk)
{
	//generate noise from seed

	Elevation.GenerateNoise(elevationSeed);
	ElevationLayerTwo.GenerateNoise(97463);
	ElevationLayerThree.GenerateNoise(35351);

	forrestNoise.GenerateNoise(forrestSeed);
	riverNoise.GenerateNoise(riverSeed);
	riverNoiseLayerTwo.GenerateNoise(riverSeed / 2);

	//Renders all he cells
	for (int x = 0; x < chunk.chunkSize; x++)
	{
		for (int y = 0; y < chunk.chunkSize; y++)
		{
			//Spawn the grass
			chunk.tiles[x][y]->isWalkable = true;

			//chunk.tiles[10][30]->isRoom = true;

			//Generate the grass
			generateGround(chunk, x, y);

		}
	}
	//SpawnTown(chunk);
	//spawnTrees(chunk);
	//spawnVegetation(chunk);
}

void ProceduralTerrain::generateGround(Chunk& chunk, int x, int y)
{
	int noiseX = chunk.tiles[x][y]->getX();
	int noiseY = chunk.tiles[x][y]->getY();
	double terrainElevation = Elevation.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20;
	double terrainElevationTwo = ElevationLayerTwo.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20;
	double terrainElevationThree = ElevationLayerThree.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20;

	//terrainElevation = (char)((terrainElevation - 0) * (255 / (terrainElevation - 0)));
	terrainElevation = terrainElevation + terrainElevationTwo + terrainElevationThree;
	

	double fNoise = forrestNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20;
	double pNoise = (riverNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20) + (riverNoiseLayerTwo.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20);
	
	
	chunk.tiles[x][y]->terrainElevationValue = terrainElevation;

	// TERRAIN NOISE
	if (terrainElevation > -0.7 && terrainElevation < 13.0)
	{
		chunk.tiles[x][y]->isGrass = true;
	}
	else if (terrainElevation > -0.5 && terrainElevation < -0.7)
	{
		chunk.tiles[x][y]->isDirt = true;
	}
	else if (terrainElevation > -2 && terrainElevation < -0.5)
	{
		chunk.tiles[x][y]->isSand = true;
		chunk.tiles[x][y]->isGrass = false;
		chunk.tiles[x][y]->isWater = false;
	}
	else if (terrainElevation < -2)
	{
		chunk.tiles[x][y]->isWater = true;
	}
	else if (terrainElevation > 25)
	{
		chunk.tiles[x][y]->isSnow = true;
	}

	// FORREST NOISE
	if (chunk.tiles[x][y]->isGrass && fNoise > 14.0)
	{
		chunk.tiles[x][y]->isVegetation = true;
		chunk.tiles[x][y]->isOakTree = true;
	}
	else if (chunk.tiles[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0)
	{

		chunk.tiles[x][y]->isVegetation = true;
		chunk.tiles[x][y]->isFernTree = true;
	}

	// PATH NOISE
	if (pNoise > 0.5 && pNoise < 1.0)
	{
		chunk.tiles[x][y]->isWater = true;

	}
	else if (pNoise >= 1.0 && pNoise < 1.3 || pNoise >= 0.3 && pNoise <= 0.5 && chunk.tiles[x][y]->isGrass)
	{
		chunk.tiles[x][y]->isSand = true;
	}
}

