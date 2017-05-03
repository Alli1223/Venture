#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "Level.h"
#include "point.h"
#include "Camera.h"
#include "AgentManager.h"

class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	PerlinNoise groundNoise;
	PerlinNoise forrestNoise;
	PerlinNoise pathNoise;


	//! Getters and setters for seed
	int getSeed() { return seed; }
	int setSeed(int newSeed) { return seed = newSeed; }

	//void ProceduralTerrain::makeGrid(int Window_Width, int Window_Height);

	void ProceduralTerrain::spawnTrees(Level& level);
	void ProceduralTerrain::spawnVegetation(Level& level);
	void ProceduralTerrain::generateGrass(Level& level, int x, int y);
	void ProceduralTerrain::populateTerrain(Level& level);
	void ProceduralTerrain::GenerateTerrain(Level& level, AgentManager& agentManager);
	void ProceduralTerrain::SpawnTown(Level& level);


	//! The base grid that contains the cells
	//std::vector<std::vector<std::shared_ptr<Cell>>> grid;

private:
	int seed = 5653876;
	int forrestSeed = seed + 30;
	int groundSeed = seed + 36945;
	int pathSeed = seed + 1255;

	int numOfTowns = 2;
	int townSize = 50;

	int generateTerrainXPos = 0, generateTerrainYPos = 0;

	float terrainNoiseOffest = 180.0;
	float forrestNoiseOffset = 180.0;

	float forrestAmplifier = 1.5;

	int numberOfTrees = 5000;
	int numberOfPlants = 10000;

};

