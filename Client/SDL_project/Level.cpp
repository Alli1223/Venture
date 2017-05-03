#include "stdafx.h"
#include "Level.h"


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
		grid.push_back(column);
		for (int y = originY; y < Level_Height + originY; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x - center,y - center);
			
			auto sharedCell = std::make_shared<Cell> (cell);
			grid[x].push_back(sharedCell);
	
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
			Cell cell(grid.size(), y);

			auto sharedCell = std::make_shared<Cell>(cell);
			grid[0].push_back(sharedCell);
		}
	}

}

Level::Level()
{
}


Level::~Level()
{
}
