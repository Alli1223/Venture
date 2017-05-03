#include "stdafx.h"
#include "CellRendering.h"

//! Constructor that initalises all the texture file locations
CellRendering::CellRendering() : roomCell(RoomSpriteTextureLocation + "center.png"), emptyCell(RoomSpriteTextureLocation + "emptyCell.png"),
	topRoomCell(RoomSpriteTextureLocation + "top.png"), topRightRoomCell(RoomSpriteTextureLocation + "topRight.png"), rightRoomCell(RoomSpriteTextureLocation + "right.png"), bottomRightRoomCell(RoomSpriteTextureLocation + "bottomRight.png"), bottomRoomCell(RoomSpriteTextureLocation + "bottom.png"), bottomLeftRoomCell(RoomSpriteTextureLocation + "bottomLeft.png"), leftRoomCell(RoomSpriteTextureLocation + "left.png"), topLeftRoomCell(RoomSpriteTextureLocation + "topLeft.png"),
	cargoBayTexture(RoomSpriteTextureLocation + "cargoBayStorage.png"), cargoTexture("Resources\\roomSprites\\crate1.png"),
	openDoorTexture(RoomSpriteTextureLocation + "center.png"),
	closedDoorTexture(RoomSpriteTextureLocation + "door.png"),
	oxygenTex("Resources\\oxygen.png"),
	oxygenTank(ItemsSpriteTextureLocation + "oxygenTank.png"), healthPack(ItemsSpriteTextureLocation + "healthPack.png"),
	healthBar("Resources\\health.png"),
	healthText("Resources\\healthText.png"),
	winTexture("Resources\\oxygenBar.png"),
	winText("Resources\\you_win.png"),
	oxygenBar("Resources\\oxygenBar.png"),
	oxygenText("Resources\\oxygenText.png"),
	gameOver("Resources\\health.png"),
	gameOverText("Resources\\game_over.png"),
	fireTexture(ItemsSpriteTextureLocation + "fire1.png"),
	backgroundTexture("Resources\\background.png"),
	hullBreachTexture("Resources\\roomSprites\\hullBreach2.png"),
	deathAnim("Resources\\deathAnim.png"),
	goalTexture("Resources\\roomSprites\\crate1.png"),
	bedSideTexture(RoomSpriteTextureLocation + "Bed.png"),
	toiletTexture(RoomSpriteTextureLocation + "wc.png"),
	kitchenTexture(RoomSpriteTextureLocation + "cargoBayStorage.png"),
	Grass1Texture(TerrainSpriteTextureLocation + "Grass.png"),
	Grass2Texture(TerrainSpriteTextureLocation + "Grass2.png"),
	OakTreeTexture(TerrainSpriteTextureLocation + "OakTree.png"),
	FernTreeTexture(TerrainSpriteTextureLocation + "FernTree.png"),
	DirtTexture(TerrainSpriteTextureLocation + "Dirt.png"),
	Flower1Texture(TerrainSpriteTextureLocation + "Flower1.png"),
	Flower2Texture(TerrainSpriteTextureLocation + "Flower2.png"),
	BerryPlantTexture(TerrainSpriteTextureLocation + "Berry.png"),
	BushTexture(TerrainSpriteTextureLocation + "Bush.png"),
	WaterTexture(TerrainSpriteTextureLocation + "Water.png"),
	SandTexture(TerrainSpriteTextureLocation + "Sand.png"),
	LongGrass1(TerrainSpriteTextureLocation + "LongGrass1.png"),
	LongGrass2(TerrainSpriteTextureLocation + "LongGrass2.png"),
	LongGrass3(TerrainSpriteTextureLocation + "LongGrass3.png"),
	StoneWallTexture(TerrainSpriteTextureLocation + "StoneWall.png"),
	TreeOneTexture(TreeTerrainSpriteTextureLocation + "Tree1.png"),
	TreeTwoTexture(TreeTerrainSpriteTextureLocation + "Tree2.png"),
	TreeThreeTexture(TreeTerrainSpriteTextureLocation + "Tree3.png")

{
}

//! Destructor
CellRendering::~CellRendering()
{
}

//! Renders the cells
void CellRendering::RenderCells(Level& level, SDL_Renderer* renderer, int x, int y, int xOffset, int yOffset)
{
	int cellSize = level.getCellSize();
	int xPos = x * cellSize + cellSize / 2;
	int yPos = y * cellSize + cellSize / 2;
	y = y + yOffset;
	x = x + xOffset;
	//RENDERING THE CELLS
	//Grass1Texture.alterTextureColour(level.grid[x][y]->noiseValue * 10, 0, 0);

	// VEGETATION


	//Base Ground Textures
	if (level.grid[x][y]->isGrass)
		if (sin(level.grid[x][y]->terrainNoiseValue) > 0.5)
			Grass1Texture.render(renderer, xPos, yPos, cellSize, cellSize);
		else
			Grass2Texture.render(renderer, xPos, yPos, cellSize, cellSize);
	if (level.grid[x][y]->isDirt)
		DirtTexture.render(renderer, xPos, yPos, cellSize, cellSize);
	if (level.grid[x][y]->isWater)
		WaterTexture.render(renderer, xPos, yPos, cellSize, cellSize);
	if (level.grid[x][y]->isSand)
		SandTexture.render(renderer, xPos, yPos, cellSize, cellSize);
	if(level.grid[x][y]->isStoneWall)
		StoneWallTexture.render(renderer, xPos, yPos, cellSize, cellSize);


	if (level.grid[x][y]->isVegetation)
	{
		//Trees
		if (level.grid[x][y]->isFernTree)
			FernTreeTexture.render(renderer, xPos, yPos - cellSize, cellSize, cellSize * 3);
		if (level.grid[x][y]->isOakTree)
			OakTreeTexture.render(renderer, xPos, yPos - cellSize, cellSize, cellSize * 3);
		if (level.grid[x][y]->isTreeOne)
			TreeOneTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		if (level.grid[x][y]->isTreeTwo)
			TreeTwoTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		if (level.grid[x][y]->isTreeThree)
			TreeThreeTexture.render(renderer, xPos, yPos, cellSize, cellSize);

		//Flowers
		if (level.grid[x][y]->isFlower1)
			Flower1Texture.render(renderer, xPos, yPos, cellSize / 3, cellSize / 2);
		if (level.grid[x][y]->isFlower2)
			Flower2Texture.render(renderer, xPos, yPos, cellSize / 3, cellSize / 2);
		if (level.grid[x][y]->isBerryPlant)
			BerryPlantTexture.render(renderer, xPos, yPos, cellSize / 2, cellSize / 1.5);
		if (level.grid[x][y]->isBush)
			BushTexture.render(renderer, xPos, yPos, cellSize / 2, cellSize / 1.5);

		//Grass
		if (level.grid[x][y]->isLongGrass)
		{
			int randVal = 0;
			if (randVal == 0)
				LongGrass1.render(renderer, xPos, yPos, cellSize, cellSize);
			else if (randVal == 1)
				LongGrass2.render(renderer, xPos, yPos, cellSize, cellSize);
			else
				LongGrass3.render(renderer, xPos, yPos, cellSize, cellSize);
		}
	}



	/*
	if (level.grid[x][y]->isRoom)
	{
		roomCell.alterTextureColour(level.grid[x][y]->noiseValue, 0, 0);
		oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel);
		roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
		oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);

		// Removes Oxyen from levels
		if (level.grid[x][y]->getOxygenLevel() > 0 && level.grid[x][y]->getOxygenLevel() <= 100)
			level.grid[x][y]->setOxygenLevel(level.grid[x][y]->getOxygenLevel() - 0.5);
	}
	*/

	// Old code
	{
		if (!level.grid[x][y]->isRoom)
		{
			level.grid[x][y]->setOxygenLevel(0);
			emptyCell.alterTransparency(0);
			emptyCell.render(renderer, xPos, yPos, cellSize, cellSize);
		}

		// Renders the top cell orientation
		if (level.grid[x][y]->cellOrientation == 0)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			topRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 1)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			topRightRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 2)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			rightRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 3)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			bottomRightRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 4)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			bottomRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 5)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			bottomLeftRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 6)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			leftRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 7)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			topLeftRoomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 8)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel / 2);
			roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->cellOrientation == 10)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel);
			roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
			level.grid[x][y]->isWalkable = true;
		}
		if (level.grid[x][y]->cellOrientation == 11)
		{
			level.grid[x][y]->setOxygenLevel(0);
			emptyCell.alterTransparency(0);
			emptyCell.render(renderer, xPos, yPos, cellSize, cellSize);
		}

		// Checks if the cell is a door
		if (level.grid[x][y]->isOpenDoor)
		{
			openDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}

		// Checks if the cell is a door
		if (level.grid[x][y]->isDockingPath)
		{
			hullBreachTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}

		// Renders the fire cells
		if (level.grid[x][y]->isOnFire)
		{
			fireTexture.alterTransparency(150);
			fireTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		// Renders the hullBreach
		if (level.grid[x][y]->isHullBreach)
		{
			level.grid[x][y]->setOxygenLevel(0);
			hullBreachTexture.alterTransparency(150);
			hullBreachTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		// Renders the oxygen Tanks
		if (level.grid[x][y]->isOxygenTank)
		{
			oxygenTank.alterTransparency(200);
			oxygenTank.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isHealthPack)
		{
			healthPack.alterTransparency(200);
			healthPack.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		// Renders open doors
		if (level.grid[x][y]->isOpenDoor)
		{
			level.grid[x][y]->setOxygenLevel(0);
			closedDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		// Renders closed doors
		if (level.grid[x][y]->isClosedDoor)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel);
			openDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		//Checks if the cell has the goal on it.
		if (level.grid[x][y]->isGoal)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel);
			roomCell.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
			goalTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isVerticalAirlock)
		{
			closedDoorTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isAirlockWall)
		{
			goalTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isShipCargoBay)
		{
			oxygenTex.alterTransparency(level.grid[x][y]->oxygenLevel);
			cargoBayTexture.render(renderer, xPos, yPos, cellSize, cellSize);
			oxygenTex.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isCargo)
		{
			cargoTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isBed)
		{
			bedSideTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isToilet)
		{
			toiletTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
		if (level.grid[x][y]->isKitchen)
		{
			kitchenTexture.render(renderer, xPos, yPos, cellSize, cellSize);
		}
	}
}