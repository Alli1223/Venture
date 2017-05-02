#pragma once
#include "Cell.h"

//! This class generates the base of the level 
/*!
This class creates a vector of vector of shared pointers to cells
*/

class Level
{
public:
	//! A constructor
	Level();
	//! A deconstructor 
	~Level();

	//! Return the cellSize
	int getCellSize() { return cellSize; }
	int setCellSize(int newCellSize) { return cellSize = newCellSize; }
	int getLevelWidth() { return levelWidth; }
	int getLevelHeight() { return levelHeight; }

	//! The base grid that contains the cells
	std::vector<std::vector<std::shared_ptr<Cell>>> grid;

	//! Stores the value for the center of the level so that the grid can spawn cells in the negative direction
	const unsigned int centerOfArray = 1000000;

	//! Fills grid with vectors of shared pointers to cells
	void makeOrExtendGrid(int Level_Width, int Level_Height, int originX, int originY);
	void Level::addRowToGrid(std::string direction, int numberOfRows);


protected:
	int x = 0, y = 0;
	//! The size that the cell will be rendered at
	int cellSize = 5;
	int levelWidth, levelHeight;
};

