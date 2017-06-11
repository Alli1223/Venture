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
	PixelTexture(TreeTerrainSpriteTextureLocation + "pixelTree.png"),
	TreeTwoTexture(TreeTerrainSpriteTextureLocation + "Tree2.png"),
	TreeThreeTexture(TreeTerrainSpriteTextureLocation + "Tree3.png"),
	SnowTexture(TerrainSpriteTextureLocation + "Snow.png")

{
}

//! Destructor
CellRendering::~CellRendering()
{
}

void CellRendering::RenderChunk(Level& level,Camera& camera, Chunk& chunk, SDL_Renderer* renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = level.getCellSize();

	for(int x = 0; x < level.getChunkSize(); x++)
		for (int y = 0; y < level.getChunkSize(); y++)
		{
			newX = chunk.tiles[x][y]->getX();
			newY = chunk.tiles[x][y]->getY();

			xPos = newX * cellSize + cellSize / 2;
			yPos = newY * cellSize + cellSize / 2;

			xPos -= camera.getX();
			yPos -= camera.getY();

			if (chunk.tiles[x][y]->isWater)
				WaterTexture.render(renderer, xPos, yPos, cellSize, cellSize);
			else
			{
				//B ase Ground Textures rendered in decending order (Top layered textures at bottom of list)
				if (chunk.tiles[x][y]->isGrass)
					Grass1Texture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isFlower1)
					Flower1Texture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isDirt)
					DirtTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isWater)
					WaterTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isSand)
					SandTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isStoneWall)
					StoneWallTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isFernTree)
					FernTreeTexture.render(renderer, xPos, yPos - cellSize, cellSize, cellSize * 3);
				if (chunk.tiles[x][y]->isOakTree)
					OakTreeTexture.render(renderer, xPos, yPos - cellSize, cellSize, cellSize * 3);
				if (chunk.tiles[x][y]->isTreeOne)
					PixelTexture.render(renderer, xPos - (cellSize * 3), yPos, cellSize * 6, cellSize * 6);
				if (chunk.tiles[x][y]->isTreeTwo)
					TreeTwoTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isTreeThree)
					TreeThreeTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk.tiles[x][y]->isFlower1)
					Flower1Texture.render(renderer, xPos, yPos, cellSize / 3, cellSize / 2);
				if (chunk.tiles[x][y]->isFlower2)
					Flower2Texture.render(renderer, xPos, yPos, cellSize / 3, cellSize / 2);
				if (chunk.tiles[x][y]->isBerryPlant)
					BerryPlantTexture.render(renderer, xPos, yPos, cellSize / 2, cellSize / 1.5);
				if (chunk.tiles[x][y]->isBush)
					BushTexture.render(renderer, xPos, yPos, cellSize / 2, cellSize / 1.5);
				if (chunk.tiles[x][y]->isLongGrass)
					LongGrass1.render(renderer, xPos, yPos, cellSize, cellSize);
				if(chunk.tiles[x][y]->isSnow)
					SnowTexture.render(renderer, xPos, yPos, cellSize, cellSize);
			}
		}
}

//! Renders the chunks of cells
void CellRendering::RenderCells(Level& level, SDL_Renderer* renderer, Camera& camera)
{
	int cellSize = level.getCellSize();		
	
	//RENDERING THE CELLS
	for (int i = (camera.getX() / cellSize) / level.getChunkSize() - 1; i < ((camera.getX() / cellSize) / level.getChunkSize()) + camera.ChunksOnScreen.x; i++)
		for (int j = (camera.getY() / cellSize) / level.getChunkSize() - 1; j < ((camera.getY() / cellSize) / level.getChunkSize()) + camera.ChunksOnScreen.y; j++)
				RenderChunk(level,camera, level.World[i][j], renderer);

}