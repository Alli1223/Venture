#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include "Chunk.h"
#include "point.h"
#include "Camera.h"


class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	//! Elevation noise
	PerlinNoise Elevation;
	PerlinNoise ElevationLayerTwo;
	PerlinNoise ElevationLayerThree;
	SimplexNoise simNoise;

	//! Other noise generations
	PerlinNoise forrestNoise;
	PerlinNoise riverNoise;
	PerlinNoise riverNoiseLayerTwo;


	//! Getters and setters for seed
	int getSeed() { return seed; }
	int setSeed(int newSeed) { return seed = newSeed; }

	//! function that calls the functions below
	void ProceduralTerrain::populateTerrain(Chunk& level);
	//! Spawns the trees in a chunk
	void ProceduralTerrain::spawnTrees(Chunk& level);
	//! Spawn the vegetation
	void ProceduralTerrain::spawnVegetation(Chunk& level);
	//! Generate the ground based of the elevation and climate
	void ProceduralTerrain::generateGround(Chunk& level, int x, int y);
	//! Spawn town (Not used)
	void ProceduralTerrain::SpawnTown(Chunk& level);

private:
	//! Seed values are random
	int seed = 573932;
	int forrestSeed = seed + 30;
	int elevationSeed = seed + 36945;
	int riverSeed = seed + 1255;

	int numOfTowns = 2;
	int townSize = 50;

	bool thereIsClimate = false;

	float terrainNoiseOffest = 180.0;
	float forrestNoiseOffset = 180.0;

	float forrestAmplifier = 1.5;

	int numberOfTrees = 5;
	int numberOfPlants = 8;

};

