#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
	Elevation.GenerateNoise(elevationSeed);
	ElevationLayerTwo.GenerateNoise(elevationSeed - 1234);
	ElevationLayerThree.GenerateNoise(elevationSeed + 1234);


	forrestNoise.GenerateNoise(forrestSeed);
	riverNoise.GenerateNoise(riverSeed);
	riverNoiseLayerTwo.GenerateNoise(riverSeed / 2);
}


ProceduralTerrain::~ProceduralTerrain()
{
}

void ProceduralTerrain::spawnRandomTrees(Chunk& chunk)
{
	for (int i = numberOfTrees; i > 0; i--)
	{
		int x = rand() % chunk.tiles.size();
		int y = rand() % chunk.tiles[0].size();
		if (!chunk.tiles[x][y]->isVegetation && !chunk.tiles[x][y]->isWater && !chunk.tiles[x][y]->isSand && !chunk.tiles[x][y]->isTown)
		{
			chunk.tiles[x][y]->isVegetation = true;
			chunk.tiles[x][y]->isWalkable = false;

			int treeType = rand() % 3;
			if (treeType <= 0)
			{
				chunk.tiles[x][y]->isFernTree = true;
				chunk.tiles[x][y]->isWalkable = false;
			}
			else
			{
				chunk.tiles[x][y]->isTreeTwo = true;
				chunk.tiles[x][y]->isWalkable = false;
			}
		}
	}
}

void ProceduralTerrain::spawnRandomVegetation(Chunk& chunk)
{	
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
			
		}
	}
}


void ProceduralTerrain::populateTerrain(Chunk& chunk)
{
	//Renders all he cells
	for (int x = 0; x < chunk.getChunkSize(); x++)
	{
		for (int y = 0; y < chunk.getChunkSize(); y++)
		{
			//Generate the grass
			generateGround(chunk, x, y);

		}
	}
	spawnRandomTrees(chunk);
	spawnRandomVegetation(chunk);
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
		if (terrainElevation >= -1.8 && terrainElevation <= 20.0)
		{
			chunk.tiles[x][y]->isGrass = true;
		}
		else if (terrainElevation >= -2.3 && terrainElevation < -1.8)
		{
			chunk.tiles[x][y]->isSand = true;
			chunk.tiles[x][y]->isGrass = true;
			chunk.tiles[x][y]->isWater = false;
		}
		else if (terrainElevation < -2.3)
		{
			chunk.tiles[x][y]->isWater = true;
		}
		else if (terrainElevation > 20.0)
		{
			chunk.tiles[x][y]->isSnow = true;
		}

		// FORREST NOISE
		if (chunk.tiles[x][y]->isGrass && fNoise > 14.0 && rand() % numberOfTrees == 1)
		{
			chunk.tiles[x][y]->isVegetation = true;
			chunk.tiles[x][y]->isOakTree = true;
			chunk.tiles[x][y]->isWalkable = false;
		}
		else if (chunk.tiles[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0 && rand() % numberOfTrees == 1)
		{
			chunk.tiles[x][y]->isVegetation = true;
			chunk.tiles[x][y]->isFernTree = true;
			chunk.tiles[x][y]->isWalkable = false;

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

