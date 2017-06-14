#include "stdafx.h"
#include "Agent.h"


Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::Update(Level& level)
{
	// Set agents cell x & y tile values & point values
	int cellSize = level.getCellSize();
	setCellX(getX() / level.getCellSize());
	setCellY(getY() / level.getCellSize());
	getAgentPointLocation() = Point(getCellX(), getCellY());

	// Decrease/Increase stats over time
	tiredness = tiredness + tirednessDecayRate;
	hunger = hunger - hungerDecayRate;
	toiletLevel = toiletLevel + toiletDecayRate;
	

	// ROTATE AGENT /////
	if (rotation == 360 - rotationSpeed || rotation == 360)
		rotation = 0;
	if (rotation == -90 - rotationSpeed || rotation == -90)
		rotation = 270;
	// Perform agent rotation based on player input
	if (rotation != targetRotation)
	{
		// Edge case
		if (rotation == 270 && targetRotation == 0)
			targetRotation = 360;
		if (rotation == 0 && targetRotation == 270)
			targetRotation = -90;

		if (rotation < targetRotation)
			rotation += rotationSpeed;
		else if (rotation > targetRotation)
			rotation -= rotationSpeed;
	}

	// Determines what direction the user accesses cells based on direction
	if (rotation == 90)
		cellInteractionDirection.x = -1;
	else if (rotation == 180)
		cellInteractionDirection.y = -1;
	else if (rotation == 270)
		cellInteractionDirection.x = +1;
	else if (rotation == 0 || 360)
		cellInteractionDirection.y = +1;
	else
	{
		cellInteractionDirection.x = 0;
		cellInteractionDirection.y = 0;
	}


	//Set chunk and cell positions for the agent
		chunkPos.x = (getX() / cellSize) / level.getChunkSize();
		chunkPos.y = (getY() / cellSize) / level.getChunkSize();

		int x = getX() / cellSize;
		int y = getY() / cellSize;
		cellPos.x = x - (chunkPos.x * level.getChunkSize());
		cellPos.y = y - (chunkPos.y * level.getChunkSize());

		if (cellPos.x < 0)
		{
			cellPos.x += level.getChunkSize();
			chunkPos.x -= 1;
		}
		if (cellPos.y < 0)
		{
			cellPos.y += level.getChunkSize();
			chunkPos.y -= 1;
		}

		//std::cout << chunkPos.x << " " << chunkPos.y << " | " << cellPos.x << " " << cellPos.y << std::endl;



	
	//if (!level.World[chunkPos.x][chunkPos.y].tiles[cellPos.x][cellPos.y]->isWater)
		//level.World[chunkPos.x][chunkPos.y].tiles[cellPos.x][cellPos.y]->isWater = true;

	
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	// Erase path
	path.erase(path.begin(), path.end());
	pathPointIterator = 0;

	// Move along path
	path = pathfinder.findPath(level, StartPoint, EndPoint);
	if (path.size() > 0)
	{
		movementStatus = TraversingPath;
		this->isMoving = true;
	}
}
