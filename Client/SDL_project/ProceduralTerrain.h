#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "Level.h"
#include "point.h"

class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	PerlinNoise groundNoise;
	PerlinNoise forrestNoise;


	//! Getters and setters for seed
	int getSeed() { return seed; }
	int setSeed(int newSeed) { return seed = newSeed; }

	//void ProceduralTerrain::makeGrid(int Window_Width, int Window_Height);

	void ProceduralTerrain::spawnTrees(Level& level);
	void ProceduralTerrain::spawnVegetation(Level& level);
	void ProceduralTerrain::generateGrass(Level& level, int x, int y);

	void ProceduralTerrain::populateTerrain(Level& level);

	//! The base grid that contains the cells
	//std::vector<std::vector<std::shared_ptr<Cell>>> grid;

private:
	int seed = SDL_GetTicks();
	int grassSeed = seed + 12;
	int groundSeed = seed + 30;

	float terrainNoiseOffest = 180.0;
	float forrestNoiseOffset = 180.0;

	float forrestAmplifier = 1.5;

	int numberOfTrees = rand();
	int numberOfPlants = 10000;

};

