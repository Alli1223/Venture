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
	cellData["X"] = x;
	cellData["Y"] = y;
	if(isWoodFence)
		cellData["Fence"] = isWoodFence;
	if(isDirt)
		cellData["Dirt"] = isDirt;
	if(isGrass)
		cellData["Grass"] = isGrass;
	if(isWood)
		cellData["Wood"] = isWood;
	if(isRock)
		cellData["Stone"] = isRock;
	if(isStoneWall)
		cellData["StoneWall"] = isStoneWall;
	if(isWheat)
		cellData["Wheat"] = isWheat;
	if(seedsStage >= 0)
		cellData["PlantStage"] = seedsStage;
	
	
	return cellData;
}

void Cell::setCell(json& jsonData)
{

	x = jsonData.at("X").get<int>();
	y = jsonData.at("Y").get<int>();

	isWoodFence = jsonData.at("Fence").get<bool>();
	isDirt = jsonData.at("Dirt").get<bool>();
	isGrass = jsonData.at("Grass").get<bool>();
	isWood = jsonData.at("Wood").get<bool>();
	isRock = jsonData.at("Stone").get<bool>();
	isStoneWall = jsonData.at("StoneWall").get<bool>();
	isWheat = jsonData.at("Wheat").get<bool>();
	//Work around for json to enum
	int plantGrowthStage = jsonData.at("PlantStage").get<int>();
	seedsStage = (Cell::seedsGrowthStage)plantGrowthStage;

}