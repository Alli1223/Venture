#include "stdafx.h"
#include "Level.h"


void Level::CreateChunk(int initX, int initY)
{
	Chunk chunk(initX, initY);
	
	for (int x = 0; x < chunkSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;
		
		World[initX][initY].tiles.push_back(column);
		for (int y = 0; y < chunkSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x + (initX * chunkSize), y + (initY * chunkSize));
			cell.renderLayer = 0;
			cell.isWalkable = true;
			auto sharedCell = std::make_shared<Cell>(cell);
			World[initX][initY].tiles[x].push_back(sharedCell);
		}
	}
	
}


void Level::GenerateWorld(Camera& camera)
{
	int numOfChunksWidth = ((camera.WindowWidth / cellSize) / chunkSize) + levelGenerationRadius;
	int numOfChunksHeight = ((camera.WindowHeight /cellSize) / chunkSize) + levelGenerationRadius;
	camera.ChunksOnScreen.x = numOfChunksWidth;
	camera.ChunksOnScreen.y = numOfChunksHeight;
	int numOfChunksGen = 0;
	for (int i = ((camera.getX() / cellSize) / chunkSize) - levelGenerationRadius; i < ((camera.getX() / cellSize) / chunkSize) + numOfChunksWidth; i++)
	{
		for (int j = ((camera.getY() / cellSize) / chunkSize) - levelGenerationRadius; j < ((camera.getY() / cellSize) / chunkSize) + numOfChunksHeight; j++)
		{
			if (!World[i][j].tiles.size() > 0)
			{
				CreateChunk(i, j);
				proceduralTerrain.populateTerrain(World[i][j]);
				numOfChunksGen++;
			}
		}
	}
	if(numOfChunksGen > 0)
		std::cout << "Generated " << numOfChunksGen << " chunks." << std::endl;
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
	returnPoint.x = World[chunkX][chunkY].tiles[cellX][cellY]->getX() + (camera.getX() * chunkSize);
	returnPoint.y = World[chunkX][chunkY].tiles[cellX][cellY]->getY() - (camera.getY() * chunkSize);

	double elevation = World[chunkX][chunkY].tiles[cellX][cellY]->terrainElevationValue;

	std::cout << returnPoint.x << " " << returnPoint.y << "|" << chunkX - (camera.getX() / chunkSize) << " " << chunkY - (camera.getY() / chunkSize) << "|" << cellX << " " << cellY << "| " << elevation << std::endl;
	return returnPoint;
}


//set a cell with the values of another cell
void Level::SetCell(int x, int y, std::shared_ptr<Cell> newcell)
{
	// ChunkX/Y is the chunk that the cell is in
	int chunkX = x / chunkSize;
	int chunkY = y / chunkSize;

	if (x >= chunkSize)
		x = x - (chunkX * chunkSize);
	if (y >= chunkSize)
		y = y - (chunkY * chunkSize);

	std::cout << "Cell update at pos: " << x << " " << y << std::endl;
	World[chunkX][chunkY].tiles[x][y] = newcell;

}

bool Level::isCellInChunk(int x, int y)
{
	if (x >= 0 && x <= chunkSize && y >= 0 && y <= chunkSize)
		return true;
	else
		return false;
}

Level::Level()
{
	Chunk exampleChunk;
	chunkSize = exampleChunk.getChunkSize();
	exampleChunk.~Chunk();
}



Level::~Level()
{
}
