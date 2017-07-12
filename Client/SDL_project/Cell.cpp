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
	/*
	json cellData = 
	{
		{"CellData",
			// POS
			{ "Position",
				{
					{"X", x}, {"Y", y}
				}
			},
			// BOOLS
			{"grass", isGrass },
			{"dirt", isDirt },
			{"fence", isWoodFence }
		}
	};
	*/
	
	json cellData;
	//cellData["Position"] = { { "X", x },{ "Y", y } };
	cellData["X"] = x;
	cellData["Y"] = y;
	cellData["Fence"] = isWoodFence;
	cellData["Dirt"] = isDirt;
	cellData["Grass"] = isGrass;
	
	
	
	return cellData;
}