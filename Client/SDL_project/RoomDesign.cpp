#include "stdafx.h"
#include "RoomDesign.h"
#include "Map.h"


RoomDesign::RoomDesign()
{
}


RoomDesign::~RoomDesign()
{
}

void RoomDesign::designRoom(Level& room, int cellX, int cellY)
{

	//check cells are within level

		//RoomDesign::checkCenterCell(room, cellX, cellY);

		//sets the top and cell edges and other little edge cases
	if (cellX == 0 && room.tiles[cellX][cellY]->isRoom)
	{
		room.tiles[cellX][cellY]->cellOrientation = 6;
	}

	if (cellY == 0 && room.tiles[cellX][cellY]->isRoom)
	{
		room.tiles[cellX][cellY]->cellOrientation = 0;
	}
	if (cellY == 0 && cellX == 0)
	{
		room.tiles[cellX][cellY]->cellOrientation = 7;
	}

	//Sets the top row to curved edges
	if (cellX >= 1 && room.tiles[cellX][cellY]->isRoom && !room.tiles[cellX - 1][cellY]->isRoom)
	{
		room.tiles[cellX][cellY]->cellOrientation = 7;
	}
	if (cellX >= 1 && room.tiles[cellX][cellY]->isRoom && !room.tiles[cellX + 1][cellY]->isRoom)
	{
		room.tiles[cellX][cellY]->cellOrientation = 1;
	}
	//sets the left edge to curved edges
	if (cellY >= 1 && room.tiles[cellX][cellY]->isRoom && !room.tiles[cellX][cellY - 1]->isRoom)
	{
		room.tiles[cellX][cellY]->cellOrientation = 7;
	}
	if (cellY >= 1 && room.tiles[cellX][cellY]->isRoom && !room.tiles[cellX][cellY + 1]->isRoom)
	{
		room.tiles[cellX][cellY]->cellOrientation = 5;
	}
	if (cellX == 1 && cellY == 1)
	{
		room.tiles[cellX][cellY]->cellOrientation = 8;
	}



	//top
	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX - 1][cellY]->isRoom)
			{
				if (!room.tiles[cellX][cellY - 1]->isRoom)
				{
					if (room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 0;
					}
				}
			}
		}
	}




	//top and right
	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (!room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (!room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 1;
					}
				}
			}
		}

	}
	//right
	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (!room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 2;
					}
				}
			}
		}

	}

	//right and bottom
	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (!room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (!room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 3;
					}
				}
			}
		}

	}

	//bottom

	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (!room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 4;
					}
				}
			}
		}

	}

	//bottom and left

	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (!room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (!room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 5;
					}

				}
			}
		}

	}

	//left

	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (!room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 6;
					}
				}
			}
		}

	}

	//left and top

	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (!room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (!room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 7;
					}
				}
			}
		}
	}

	//center

	if (room.tiles[cellX][cellY]->isRoom)
	{
		if (room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 10;
						room.tiles[cellX][cellY]->isWalkable = true;
					}
				}
			}
		}
	}

	// No center
	if (!room.tiles[cellX][cellY]->isRoom)
	{
		if (!room.tiles[cellX + 1][cellY]->isRoom)
		{
			if (!room.tiles[cellX][cellY - 1]->isRoom)
			{
				if (!room.tiles[cellX][cellY + 1]->isRoom)
				{
					if (!room.tiles[cellX - 1][cellY]->isRoom)
					{
						room.tiles[cellX][cellY]->cellOrientation = 11;
					}
				}
			}
		}
	}
}
	



bool RoomDesign::checkCenterCell(Level& room, int cellX, int cellY)
{
	std::vector<int> directions;

	directions.push_back(-1);
	directions.push_back(0);
	directions.push_back(1);


	for (int x = 1; x >= -1; x--)
	{
		for (int y = -1; y <= 1; y++)
		{

			//is a room and not a door
			if (room.tiles[cellX + x][cellY + y]->isRoom && !room.tiles[cellX + x][cellY + y]->isOpenDoor)
			{
				if (room.tiles[cellX + x][cellY + y]->isRoom && !room.tiles[cellX][cellY]->isRoom)
				{
					room.tiles[cellX + x][cellY + y]->isHullBreach = true;

					return true;

				}
			}
		}

	}
}
