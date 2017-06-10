#include "stdafx.h"
#include "Oxygen.h"
#include "Cell.h"
#include "Level.h"
#include "Map.h"
#include "Fire.h"
#include "AgentInteraction.h"



Oxygen::Oxygen()
{
}

Oxygen::~Oxygen()
{

}

//Increases oxygen in a selected cell (only if the cell is a room)
void Oxygen::addOxygen(int mouseX, int mouseY, int cellSize, Level tiles)
{
	//get the cell of where the mouse was clicked
	int cellX = mouseX / cellSize;
	int cellY = mouseY / cellSize;
	tiles.tiles[cellX][cellY]->oxygenLevel++;
	

}

//Decreases oxygen in a selected cell
void Oxygen::removeOxygen(Level& tiles)
{

	
}

//Loops through the cells to balance out the oxygen values
void Oxygen::update(Level& tiles, int cellX, int cellY)
{
	point = Point(cellX, cellY);
	//OxygenLevel is set to the current cell in the loop
	int oxygenLevel = tiles.tiles[cellX][cellY]->getOxygenLevel();
	int oxygenReserve = getOxygenReserves();


	//Loops through the rooms but not the doors
	if (tiles.tiles[cellX][cellY]->isRoom && !tiles.tiles[cellX][cellY]->isOpenDoor)
	{
		//check cells are within level
		if (point.getX() - 1 >= 0 && point.getX() + 1 <= tiles.getLevelWidth() && point.getY() - 1 >= 0 && point.getY() + 1 <= tiles.getLevelHeight())
		{
			//gets neighbour cells around the point
			for (auto neighbour : getNeighbourCells(point, tiles))
			{
				//check cells are within level
				if (neighbour.getX() - 1 >= 0 && neighbour.getX() + 1 <= tiles.getLevelWidth() && neighbour.getY() - 1 >= 0 && neighbour.getY() + 1 <= tiles.getLevelHeight())
				{
					// Cannot go thrugh closed doors
					if (!tiles.tiles[point.getX()][point.getY()]->isOpenDoor || !tiles.tiles[neighbour.getX()][neighbour.getY()]->isOpenDoor || !tiles.tiles[point.getX()][point.getY()]->isClosedDoor || !tiles.tiles[neighbour.getX()][neighbour.getY()]->isClosedDoor)
					{
						/*if the neighbour has 100 oxygen and current point has less than 100 increase current point
						if (grid.grid[point.getX()][point.getY()]->getOxygenLevel() < 100 && grid.grid[neighbour.getX()][neighbour.getY()]->getOxygenLevel() == 100)
						{
							grid.grid[point.getX()][point.getY()]->setOxygenLevel(grid.grid[point.getX()][point.getY()]->getOxygenLevel() + oxygenSpreadRate);
						}
						*/

						if (tiles.tiles[point.getX()][point.getY()]->getOxygenLevel() < tiles.tiles[neighbour.getX()][neighbour.getY()]->getOxygenLevel())
						{
							tiles.tiles[point.getX()][point.getY()]->setOxygenLevel(tiles.tiles[neighbour.getX()][neighbour.getY()]->getOxygenLevel());
						}
						
						if (tiles.tiles[point.getX()][point.getY()]->isOnFire)
						{
							tiles.tiles[point.getX()][point.getY()]->oxygenLevel = 0;
						}

					}
				}
			}
		}

	}
}
	

std::vector<Point> Oxygen::getNeighbourCells(Point& point, Level& tiles)
{
	//Retuns neighbouring cells
	std::vector<Point> result;

	Point leftPoint(point.getX() - 1, point.getY());
	Point rightPoint(point.getX() + 1, point.getY());
	Point topPoint(point.getX(), point.getY() - 1);
	Point bottomPoint(point.getX() - 1, point.getY() + 1);

	result.push_back(leftPoint);
	result.push_back(topPoint);
	result.push_back(rightPoint);
	result.push_back(bottomPoint);

	return result;

}