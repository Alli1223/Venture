#pragma once
#include "Texture.h"
//! 
/*!

*/
class Cell
{
public:
	//! A constructor
	Cell();
	//! An alternate constructor
	/*!
	This constructor requires an X and Y for the Cell 
	*/
	Cell(int x, int y);
	//! A destructor 
	~Cell();
	//! Gets the cells data and returns it in json format
	json getCellData();

	std::string getCellID() { return cellID; };
	std::string setCellID(std::string newCellID) { return cellID = newCellID; }

	// Getter functions
	//! Gets the Cell's X value
	int getX() const { return x; }
	//! Gets the Cell's Y value
	int getY() const { return y; }

	
	// Setter functions
	//! Sets the Cells X value
	int setX(int newX) { return x = newX; }
	//! Sets the Cells Y value
	int setY(int newY) { return y = newY; }
	//! Sets the Cells X and Y values
	int setPos(int newX, int newY) { return x = newX, y = newY; }

	int cellLightness = 255;
	

	//! Whether the cell is part of a room
	bool isRoom = false;
	//! Whether the cell is walkable
	bool isWalkable = true;

	//! Variables used for terrain
	double terrainElevationValue = 0;
	double climate = 0;

	//! Whether the cell is a bed
	bool isBed = false;
	//! Wehther the cell is a bed and in use
	bool isOccupiedBed = false;
	//! Whether the cell is a toilet
	bool isToilet = false;
	//! Whether the cell is a toilet and in use
	bool isOccupiedToilet = false;
	//! Whether the cell is a kitchen
	bool isKitchen = false;

	bool isGrass = false;
	bool isLongGrass = false;
	bool isLongGrass2 = false;
	bool isDirt = false;

	bool isTree = false;

	bool isWater = false;
	bool isSand = false;
	bool isSnow = false;

	enum TreeType
	{
		treeOne,
		treeTwo,
		treeThree,
		treeFour
	};

	bool isVegetation = false;
	bool isFlower1 = false;
	bool isFlower2 = false;
	bool isBerryPlant = false;
	bool isBush = false;

	bool isTown = false;
	bool isBuilding = false;
	bool isStoneWall = false;
	bool isWoodFence = false;

	int renderLayer = 0;

private:
	//! The Cells X and Y values
	int x = 0, y = 0;

	std::string cellID;

	int globalX = 0, GlobalY = 0;
};