
#include "stdafx.h"
#include "Fire.h"
#include "Cell.h"
#include "Level.h"


Fire::Fire()
{
}


Fire::~Fire()
{
}

// Function that spawns oxygen in the map
void Fire::spawn(Level& tiles, int cellX, int cellY)
{
	// Spawns fire once every second
	currentTime = SDL_GetTicks();
	if (currentTime > lastTime + (firespawntimer * 1000) ) 
	{
		if (tiles.tiles[cellX][cellY]->isRoom && (cellX >= 3 || cellY >= 3))
		{

			// It will not spawn on doors or oxygen tanks or hull breaches
			if (tiles.tiles[cellX][cellY]->isOpenDoor == false && tiles.tiles[cellX][cellY]->isOxygenTank == false && tiles.tiles[cellX][cellY]->isHullBreach == false && tiles.tiles[cellX][cellY]->oxygenLevel > 0)
			{
				tiles.tiles[cellX][cellY]->isOnFire = true;
				tiles.tiles[cellX][cellY]->oxygenLevel = 0;
			}
		}
		lastTime = currentTime;
	}
}


// Function that manages the spread of oxygen in the map
void Fire::fireSpread(Level& tiles, int cellX, int cellY)
{
	// If the cell is on fire, choose a random direction to spread
	if (tiles.tiles[cellX][cellY]->isOnFire == true)
	{
		int randomDirectionX = rand() % (-1 - 2) - 1;
		int randomDirectionY = rand() % (-1 - 2) - 1;


		// The new random cell is within the map
		if (cellX + (randomDirectionX) + 1 <= tiles.getLevelWidth() && cellX + (randomDirectionX) - 1 >= 0 && cellY + (randomDirectionY) + 1 <= tiles.getLevelHeight() && cellY + (randomDirectionY) - 1 >= 0)
		{
			// The new random cell is room and not a hull breach
			if (tiles.tiles[cellX + (randomDirectionX)][cellY + (randomDirectionY)]->isRoom && tiles.tiles[cellX + (randomDirectionX)][cellY + (randomDirectionY)]->isHullBreach == false)
			{
				// The new random cell is not an open door
				if ( tiles.tiles[cellX + (randomDirectionX)][cellY + (randomDirectionY)]->isOpenDoor == false)
				{
					// The cell has oxygen
					if (tiles.tiles[cellX + (randomDirectionX)][cellY + (randomDirectionY)]->getOxygenLevel() >= 25)
					{
						// Random fire spread rate
						int randomSpawnChance = rand() % (0 - spreadRate);
						if (randomSpawnChance == 0)
						{
							tiles.tiles[cellX + (randomDirectionX)][cellY + (randomDirectionY)]->isOnFire = true;
							tiles.tiles[cellX + (randomDirectionX)][cellY + (randomDirectionY)]->setOxygenLevel(0);
						}
					}
				}
			}
		}

		currentTime = SDL_GetTicks();
		if (currentTime > lastTime +  1000)
		{

			lastTime = currentTime;
		}
	}

	if (cellX + 1 < tiles.getLevelWidth() && cellX - 1 > 0 && cellY + 1 < tiles.getLevelHeight() && cellY - 1 > 0)
	{
		if (tiles.tiles[cellX + 1][cellY]->getOxygenLevel() <= 25 && tiles.tiles[cellX - 1][cellY]->getOxygenLevel() <= 25 && tiles.tiles[cellX][cellY + 1]->getOxygenLevel() <= 25 && tiles.tiles[cellX][cellY - 1]->getOxygenLevel() <= 25)
		{
			tiles.tiles[cellX][cellY]->isOnFire = false;
		}
	}
}

void Fire::fireExtinguisher()
{

}


	


