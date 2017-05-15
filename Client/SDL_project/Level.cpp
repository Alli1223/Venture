#include "stdafx.h"
#include "Level.h"


void Level::CreateChunk(int initX, int initY)
{
	Chunk chunk(initX, initY);

	for (int x = 0; x < chunk.chunkSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;
		std::cout << "Generating chunk: " << x  + (initX * chunk.chunkSize) << std::endl;
		World[initX][initY].tiles.push_back(column);
		for (int y = 0; y < chunk.chunkSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x + (initX * chunk.chunkSize), y + (initY * chunk.chunkSize));
			cell.isGrass = true;
			auto sharedCell = std::make_shared<Cell>(cell);
			World[initX][initY].tiles[x].push_back(sharedCell);
		}
	}	 
}

// Populates a 2 dimentional vector with pointers to cells
void Level::makeOrExtendGrid(int Level_Width, int Level_Height, int originX, int originY)
{
	// Calculate the number of cells on each axis
	levelWidth = Level_Width;
	levelHeight = Level_Height;
	int center = 2000;
	
	for (int x = originX; x < Level_Width + originX; x++)
	{
		// Pushes back a column into the row
		std::vector<std::shared_ptr<Cell>> column;
		tiles.push_back(column);
		for (int y = originY; y < Level_Height + originY; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x - center,y - center);
			
			auto sharedCell = std::make_shared<Cell> (cell);
			tiles[x].push_back(sharedCell);
	
		}
	}
}

//TODO add cells to grid
void Level::addRowToGrid(std::string direction, int numberOfRows)
{
	std::vector<std::shared_ptr<Cell>> column;
	if (direction == "RIGHT")
	{
		for (int y = 0; y < levelHeight; y++)
		{
			Cell cell(tiles.size(), y);

			auto sharedCell = std::make_shared<Cell>(cell);
			tiles[0].push_back(sharedCell);
		}
	}

}

Level::Level()
{
}

Level::Level(int initX, int initY)
{
	x = initX;
	y = initY;
}


Level::~Level()
{
}
