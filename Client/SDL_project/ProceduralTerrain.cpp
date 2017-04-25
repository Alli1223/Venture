#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
}


ProceduralTerrain::~ProceduralTerrain()
{
}


void ProceduralTerrain::makeGrid(int Width, int Height)
{
	// Calculate the number of cells on each axis
	int XAxis_Max = (Width);
	int YAxis_Max = (Height);
	int levelWidth = Width;
	int levelHeight = Height;
	for (int x = 0; x < XAxis_Max; x++)
	{
		// Pushes back a column into the row
		std::vector<std::shared_ptr<Cell>> column;
		grid.push_back(column);
		for (int y = 0; y < YAxis_Max; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x, y);

			auto sharedCell = std::make_shared<Cell>(cell);
			grid[x].push_back(sharedCell);
		}
	}
}


void ProceduralTerrain::populateTerrain()
{
	//generate noise from seed
	perlinNoise.GenerateNoise(SDL_GetTicks());
	for (int x = 0; x < grid.size() - 1; x++)
	{
		for (int y = 0; y < grid[0].size() - 1; y++)
		{
			grid[x][y]->isGrass = true;
			double noise = perlinNoise.noise((double)x / 180.0, (double)y / 180.0, 0.0);
			//noise = (char)((noise - 0) * (255 / (noise - 0)));
			
			grid[x][y]->noiseValue = noise * 1000;
			//Renders all he cells
			//cellrenderer.RenderCells(level, renderer, x, y);
		}
	}
}