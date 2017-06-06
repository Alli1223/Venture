#include "stdafx.h"
#include "Level.h"


void Level::CreateChunk(int initX, int initY)
{
	Chunk chunk(initX, initY);

	bool once = true;
	for (int x = 0; x < chunkSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;
		std::cout << "Generating chunk: " << x  + (initX * chunkSize) << std::endl;
		World[initX][initY].tiles.push_back(column);
		for (int y = 0; y < chunkSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x + (initX * chunkSize), y + (initY * chunkSize));
			cell.isGrass = true;

			auto sharedCell = std::make_shared<Cell>(cell);
			World[initX][initY].tiles[x].push_back(sharedCell);
		}
	}	 
}


void Level::GenerateWorld(Camera& camera)
{
	for (int i = camera.getX(); i < camera.getX() + 5; i++)
	{
		for (int j = camera.getY(); j < camera.getY() + 5; j++)
		{
			CreateChunk(i, j);
		}
		std::cout << "Creating chunk: " << i << std::endl;
	}
}


// Returns the value of the x & y values in the cell
glm::vec2 Level::GetGlobalCell(Camera& camera, int cellX, int cellY)
{
	glm::vec2 returnPoint;
	// ChunkX/Y is the chunk that the cell is in
	int chunkX = cellX / chunkSize;
	int chunkY = cellY / chunkSize;

	// Get x and y values of each chunk
	if (cellX >= chunkSize)
		cellX = cellX - (chunkX * chunkSize);
	if (cellY >= chunkSize)
		cellY = cellY - (chunkY * chunkSize);
	
	// ReturPoint is the value of the x/y values in the cell (takes into account the camera position)
	returnPoint.x = World[chunkX][chunkY].tiles[cellX][cellY]->getX() - (camera.getX() * chunkSize);
	returnPoint.y = World[chunkX][chunkY].tiles[cellX][cellY]->getY() - (camera.getY() * chunkSize);

	std::cout << returnPoint.x << " " << returnPoint.y << "|" << chunkX << " " << chunkY << "|" << cellX << " " << cellY << std::endl;
	return returnPoint;
}


//NOt used
void Level::SetGlobalCell(Camera& camera, int x, int y)
{
	// ChunkX/Y is the chunk that the cell is in
	int chunkX = x / chunkSize;
	int chunkY = y / chunkSize;
	// Get x and y values of each chunk
	if (x >= chunkSize)
		x = x - (chunkX * chunkSize);
	if (y >= chunkSize)
		y = y - (chunkY * chunkSize);

	World[chunkX][chunkY].tiles[x][y]->isFlower1 = true;

}

Level::Level()
{
}



Level::~Level()
{
}
