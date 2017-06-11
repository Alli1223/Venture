#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
}


ProceduralTerrain::~ProceduralTerrain()
{
}

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
}

void ProceduralTerrain::spawnVegetation(Chunk& chunk)
{	
	int numPlants = 0;
	for (int i = numberOfPlants; i > 0; i--)
	{
		int x = rand() % chunk.tiles.size();
		int y = rand() % chunk.tiles[0].size();
		
		if (!chunk.tiles[x][y]->isVegetation && !chunk.tiles[x][y]->isWater && !chunk.tiles[x][y]->isSand)
		{
			chunk.tiles[x][y]->isVegetation = true;
			int vegType = rand() % 3;
			//Item item;
			switch (vegType)
			{
			case 0:
				chunk.tiles[x][y]->isVegetation = true;
				chunk.tiles[x][y]->isFlower1 = true;
				break;
			case 1:
				chunk.tiles[x][y]->isVegetation = true;
				chunk.tiles[x][y]->isBerryPlant = true;
				//item.isBerry = true;
				//chunk.grid[x][y]->cellItem = item;
				break;
			case 2:
				chunk.tiles[x][y]->isVegetation = true;
				chunk.tiles[x][y]->isFlower2 = true;
				break;
			}
			numPlants++;
		}
	}
}


void ProceduralTerrain::populateTerrain(Chunk& chunk)
{
	//generate noise from seed

	Elevation.GenerateNoise(elevationSeed);
	ElevationLayerTwo.GenerateNoise(elevationSeed - 1234);
	ElevationLayerThree.GenerateNoise(elevationSeed + 1234);
	

	forrestNoise.GenerateNoise(forrestSeed);
	riverNoise.GenerateNoise(riverSeed);
	riverNoiseLayerTwo.GenerateNoise(riverSeed / 2);

	//Renders all he cells
	for (int x = 0; x < chunk.getChunkSize(); x++)
	{
		for (int y = 0; y < chunk.getChunkSize(); y++)
		{
			//Spawn the grass
			chunk.tiles[x][y]->isWalkable = true;

			//Generate the grass
			generateGround(chunk, x, y);

		}
	}
	//SpawnTown(chunk);
	spawnTrees(chunk);
	spawnVegetation(chunk);
}

//TODO: Put all constant values in the headder
void ProceduralTerrain::generateGround(Chunk& chunk, int x, int y)
{
	float noiseX = chunk.tiles[x][y]->getX();
	float noiseY = chunk.tiles[x][y]->getY();
	double terrainElevation = Elevation.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20.0;
	double terrainElevationTwo = ElevationLayerTwo.noise((double)noiseX / terrainNoiseOffest / 2.0, (double)noiseY / terrainNoiseOffest / 2.0, 0.0) * 20.0;
	double terrainElevationThree = ElevationLayerThree.noise((double)noiseX, (double)noiseY, 0.0) * 20.0;
	double sNoise = simNoise.noise(noiseX / 40, noiseY / 40);

	terrainElevation = sNoise + terrainElevationTwo + terrainElevation + terrainElevationThree + 2;
	double climate = sin(chunk.tiles[x][y]->getY() / 500.0);
	
	
	double fNoise = forrestNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20.0;
	fNoise += simNoise.fractal(1, noiseX / 40, noiseY / 40);
	double rNoise = (riverNoise.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0) + (riverNoiseLayerTwo.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0);
	rNoise += simNoise.noise(noiseX / 100, noiseY / 100);
	
	//set the cells terrain value
	chunk.tiles[x][y]->terrainElevationValue = terrainElevation;

	if (climate > 0 || !thereIsClimate)
	{
		// TERRAIN NOISE
		if (terrainElevation > -1.8 && terrainElevation < 13.0)
		{
			chunk.tiles[x][y]->isGrass = true;
		}
		else if (terrainElevation > -2.3 && terrainElevation < -1.8)
		{
			chunk.tiles[x][y]->isSand = true;
			chunk.tiles[x][y]->isGrass = false;
			chunk.tiles[x][y]->isWater = false;
		}
		else if (terrainElevation < -2)
		{
			chunk.tiles[x][y]->isWater = true;
		}
		else if (terrainElevation > -0.5 && terrainElevation < -0.7)
		{
			chunk.tiles[x][y]->isDirt = true;
		}


		else if (terrainElevation > 25)
		{
			chunk.tiles[x][y]->isSnow = true;
		}

		// FORREST NOISE
		if (chunk.tiles[x][y]->isGrass && fNoise > 14.0 && rand() % numberOfTrees == 1)
		{
			chunk.tiles[x][y]->isVegetation = true;
			chunk.tiles[x][y]->isOakTree = true;
		}
		else if (chunk.tiles[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0 && rand() % numberOfTrees == 1)
		{
			chunk.tiles[x][y]->isVegetation = true;
			chunk.tiles[x][y]->isFernTree = true;
		}

		// RIVER NOISE
		if (rNoise > 0.5 && rNoise < 1.0)
		{
			chunk.tiles[x][y]->isWater = true;
			chunk.tiles[x][y]->terrainElevationValue = -2.1;

		}
		else if (rNoise >= 1.0 && rNoise < 1.3 || rNoise >= 0.3 && rNoise <= 0.5 && chunk.tiles[x][y]->isGrass)
		{
			chunk.tiles[x][y]->isSand = true;
		}
	}
	else
	{
		if (terrainElevation > -1.8 && terrainElevation < 13.0)
			chunk.tiles[x][y]->isSnow = true;
		else if (terrainElevation < -2)
			chunk.tiles[x][y]->isWater = true; // Change to ice
	}
}

