#include "stdafx.h"
#include "Level.h"


// Populates a 2 dimentional vector with pointers to cells
void Level::makeGrid(int Window_Width, int Window_Height)
{
	// Calculate the number of cells on each axis
	int XAxis_Max = (Window_Width);
	int YAxis_Max = (Window_Width);
	levelWidth = Window_Width;
	levelHeight = Window_Height;
	for (int x = 0; x < XAxis_Max; x++)
	{
		// Pushes back a column into the row
		std::vector<std::shared_ptr<Cell>> column;
		grid.push_back(column);
		for (int y = 0; y < YAxis_Max; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x,y);
			
			auto sharedCell = std::make_shared<Cell> (cell);
			grid[x].push_back(sharedCell);
		}
	}
}


Level::Level()
{
}


Level::~Level()
{
}
