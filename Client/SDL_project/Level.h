#pragma once
#include "Cell.h"
#include "Chunk.h"
#include "Point.h"
#include "Camera.h"
#include "ProceduralTerrain.h"

//! This class generates the base of the level 
/*!
This class creates a vector of vector of shared pointers to cells
*/

class Level
{
public:
	//! A constructor
	Level();
	//! A deconstructor 
	~Level();

	//! Return the cellSize
	int getCellSize() { return cellSize; }
	int getChunkSize() { return chunkSize; }
	int setCellSize(int newCellSize) { return cellSize = newCellSize; }
	int getLevelWidth() { return levelWidth; }
	int getLevelHeight() { return levelHeight; }

	//! The base grid that contains the cells
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	glm::vec2 Level::GetGlobalCell(Camera& camera, int cellX, int cellY);

	void Level::SetGlobalCell(Camera& camera, int x, int y, glm::vec2 mousePos);


	void Level::GenerateWorld(Camera& camera);

	
	void Level::CreateChunk(int initX, int initY);

	std::map<int, std::map<int, Chunk>> World;


protected:
	ProceduralTerrain proceduralTerrain;
	//! The size that the cell will be rendered at
	int cellSize = 25;
	int chunkSize;

	// The extra chunks that are generated at the screens border and beyond
	int levelGenerationRadius = 2;

	int levelWidth, levelHeight;
};

