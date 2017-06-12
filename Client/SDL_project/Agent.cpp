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
	

	// If the agent has a path move along it
	if (movementStatus == TraversingPath && path.size() > 0)
	{
		float deltaY = getY() - path[pathPointIterator].getY() * level.getCellSize();
		float deltaX = getX() - path[pathPointIterator].getX() * level.getCellSize();
		

		float length = sqrt(deltaX * deltaX + deltaY * deltaY);

		// Normalize 
		deltaX /= length;
		deltaY /= length;

		// Calculate rotation
		if (agentCanRotate)
		{
			float angleInDegrees = atan2(deltaY, deltaX) * 180.0 / PI;

			// Apply correction to rotation
			rotation = angleInDegrees + 90;
		}

		// Multiply direction by magnitude 
		deltaX *= getSpeed();
		deltaY *= getSpeed();

		if (getX() - deltaX > 0 && getY() - deltaY > 0)
		{
			setX(getX() - deltaX);
			setY(getY() - deltaY);
		}
		
		// If the agent reaches the node in the path
		if (getCellX() == path[pathPointIterator].getX() && getCellY() == path[pathPointIterator].getY())
		{
			pathPointIterator++;
		}
	}
	// Perform agent rotation based on player input
	if (rotation != targetRotation)
	{
		// Edge case
		if (rotation == 270 && targetRotation == 0)
			targetRotation = 360;
		else if (rotation == 360)
			rotation = 0;

		else if (rotation == 0 && targetRotation == 270)
			targetRotation = -90;
		else if (rotation == -90)
			rotation = 270;


		if (rotation < targetRotation)
			rotation += rotationSpeed;
		else if (rotation > targetRotation)
			rotation -= rotationSpeed;
		std::cout << rotation << std::endl;
	}
	pos.a = (getX() / cellSize) / level.getChunkSize();
	pos.b = (getY() / cellSize) / level.getChunkSize();

	int x = getX() / cellSize;
	int y = getY() / cellSize;


	// Get x and y values of each chunk
	if (x >= level.getChunkSize())
		pos.x = x - (x * level.getChunkSize());
	if (y >= level.getChunkSize())
		pos.y = y - (y * level.getChunkSize());


	
	//if (level.World[pos.a][pos.b].tiles[pos.x][pos.y]->isWater)
		//level.World[pos.a][pos.b].tiles[pos.x][pos.y]->isWater = false;

	/*Add berry to inventory
	if (level.tiles[getCellX()][getCellY()]->isBerryPlant && state[SDL_SCANCODE_F])
	{
		Item berry;
		berry.isBerry = true;
		inventory.add(berry);
		level.tiles[getCellX()][getCellY()]->isBerryPlant = false;
		level.tiles[getCellX()][getCellY()]->isBush = true;
	}

	// Agent will wonder randomly when idle
	if (movementStatus == Idle && agentWonderWhenIdle)
	{
		bool foundEndPoint = false;
		Point endPoint;
		while (!foundEndPoint)
		{
			int x = rand() % level.tiles.size();
			int y = rand() % level.tiles[x].size();
			if (level.tiles[x][y]->isWalkable && level.tiles[x][y]->isRoom)
			{
				endPoint = Point(level.tiles[x][y]->getX(), level.tiles[x][y]->getY());
				foundEndPoint = true;
				movementStatus = TraversingPath;
			}
		}
		Point startPoint(this->getCellX(), this->getCellY());
		this->Move(level, startPoint, endPoint);
	}
	
	

	// If the Agent has reached the end of the path then reset the pathfinder and set the agent to idle.
	if (pathPointIterator >= path.size() && movementStatus == TraversingPath)
	{
		movementStatus = Idle;
		isMoving = false;
		pathPointIterator = 0;
	}
	*/
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
