#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
}

// 
Cell::Cell(int x, int y)
{
	setX(x);
	setY(y);
}

Cell::~Cell(){
}

json Cell::getCellData()
{	
	json cellData;
	//cellData["Position"] = { { "X", x },{ "Y", y } };
	cellData["X"] = x;
	cellData["Y"] = y;
	cellData["Fence"] = isWoodFence;
	cellData["Dirt"] = isDirt;
	cellData["Grass"] = isGrass;
	cellData["Wood"] = isWood;
	cellData["Stone"] = isRock;
	cellData["StoneWall"] = isStoneWall;
	cellData["Wheat"] = isWheat;
	cellData["PlantStage"] = seedsStage;
	
	
	return cellData;
}