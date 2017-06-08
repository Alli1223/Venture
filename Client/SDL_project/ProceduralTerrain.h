#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "Chunk.h"
#include "point.h"
#include "Camera.h"


class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	PerlinNoise Elevation;
	PerlinNoise ElevationLayerTwo;
	PerlinNoise ElevationLayerThree;

	PerlinNoise forrestNoise;
	PerlinNoise riverNoise;
	PerlinNoise riverNoiseLayerTwo;


	//! Getters and setters for seed
	int getSeed() { return seed; }
	int setSeed(int newSeed) { return seed = newSeed; }

	void ProceduralTerrain::spawnTrees(Chunk& level);
	void ProceduralTerrain::spawnVegetation(Chunk& level);
	void ProceduralTerrain::generateGround(Chunk& level, int x, int y);
	void ProceduralTerrain::populateTerrain(Chunk& level);
	void ProceduralTerrain::SpawnTown(Chunk& level);

private:
	int seed = 87653;
	int forrestSeed = seed + 30;
	int elevationSeed = seed + 36945;
	int riverSeed = seed + 1255;

	int numOfTowns = 2;
	int townSize = 50;

	float terrainNoiseOffest = 180.0;
	float forrestNoiseOffset = 180.0;

	float forrestAmplifier = 1.5;

	int numberOfTrees = 5000;
	int numberOfPlants = 10000;

};

