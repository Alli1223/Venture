#include "stdafx.h"
#include "CellRendering.h"

//! Constructor that initalises all the texture file locations
CellRendering::CellRendering() : roomCell(RoomSpriteTextureLocation + "center.png"), emptyCell(RoomSpriteTextureLocation + "emptyCell.png"),
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
	SnowTexture(TerrainSpriteTextureLocation + "Snow.png"),
	WoodFenceSide(WallSpriteTextureLocation + "woodFenceSide2.png"), WoodFenceUP(WallSpriteTextureLocation + "woodFenceUp.png"), WoodFenceCenter(WallSpriteTextureLocation + "woodFenceCenter.png"),

	characterTex(characterTextureLocation + "crew.png"), npcDown(characterTextureLocation + "npc.png"),
	healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"), hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png")

{
}

//! Destructor
CellRendering::~CellRendering()
{
}

void CellRendering::RenderChunk(Level& level, Camera& camera, Chunk& chunk, SDL_Renderer* renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = level.getCellSize();

	for (int x = 0; x < level.getChunkSize(); x++)
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
				// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
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
				else if (chunk.tiles[x][y]->isOakTree)
					OakTreeTexture.render(renderer, xPos, yPos - cellSize, cellSize, cellSize * 3);
				else if (chunk.tiles[x][y]->isTreeOne)
					PixelTexture.render(renderer, xPos - (cellSize * 3), yPos - (cellSize * 3), cellSize * 6, cellSize * 6);
				else if (chunk.tiles[x][y]->isTreeTwo)
					TreeTwoTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				else if (chunk.tiles[x][y]->isTreeThree)
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
				if (chunk.tiles[x][y]->isSnow)
					SnowTexture.render(renderer, xPos, yPos, cellSize, cellSize);

				if (chunk.tiles[x][y]->isWoodFence)
				{
					if (level.isCellInChunk(x, y + 1) && level.isCellInChunk(x, y - 1) && level.isCellInChunk(x + 1, y) && level.isCellInChunk(x - 1, y))
					{
						if (chunk.tiles[x][y]->isWoodFence && chunk.tiles[x][y + 1]->isWoodFence && chunk.tiles[x][y - 1]->isWoodFence && !chunk.tiles[x + 1][y]->isWoodFence && !chunk.tiles[x - 1][y]->isWoodFence)
							WoodFenceUP.render(renderer, xPos, yPos, cellSize, cellSize);
						else if (chunk.tiles[x][y]->isWoodFence && chunk.tiles[x][y + 1]->isWoodFence && chunk.tiles[x][y - 1]->isWoodFence && chunk.tiles[x + 1][y]->isWoodFence && chunk.tiles[x - 1][y]->isWoodFence)
							WoodFenceCenter.render(renderer, xPos, yPos, cellSize, cellSize);
						else
							WoodFenceSide.render(renderer, xPos, yPos, cellSize, cellSize);
					}
				}


			}
		}
}

//! Renders the chunks of cells
void CellRendering::RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, std::vector<Agent>& allAgents)
{
	int cellSize = level.getCellSize();		
	
	//RENDERING THE CELLS
	for (int i = (camera.getX() / cellSize) / level.getChunkSize() - 1; i < ((camera.getX() / cellSize) / level.getChunkSize()) + camera.ChunksOnScreen.x; i++)
		for (int j = (camera.getY() / cellSize) / level.getChunkSize() - 1; j < ((camera.getY() / cellSize) / level.getChunkSize()) + camera.ChunksOnScreen.y; j++)
				RenderChunk(level,camera, level.World[i][j], renderer);

	//Render Agents
	for (Agent& agent : allAgents)
		RenderAgents(agent, renderer, level, camera);
	
}

void CellRendering::RenderAgents(Agent& agent, SDL_Renderer* renderer, Level& level, Camera& camera)
{

	int x = agent.getX() + (agent.getSize() / 2) - camera.getX();
	int y = agent.getY() + (agent.getSize() / 2) - camera.getY();
	if (agent.characterType == "NPC")
	{
		//npcDown.alterTextureColour(0, rand(), 0);
		npcDown.renderRotation(renderer, x, y, agent.getSize(), agent.getSize(), agent.rotation);


		//Render agent stats to the right of agent
		if (renderStats)
		{
			if (agent.getHealth() < 100.0)
				healthBarTexture.render(renderer, x + agent.getSize() - agent.getSize() / 10, y, agent.getSize() / 10, agent.getHealth() / 2);
			if (agent.getOxygenLevel() < 100.0)
				oxygenBarTexture.render(renderer, x + agent.getSize(), y, agent.getSize() / 10, agent.getOxygenLevel() * 30.0);
			if (agent.getHunger() < 100.0)
				hungerBarTexture.render(renderer, x + agent.getSize() + agent.getSize() / 10, y, agent.getSize() / 10, agent.getHunger() * 30.0);
			if (agent.getTiredness() > 0.0)
				tiredBarTexture.render(renderer, x + agent.getSize() + agent.getSize() * 2 / 10, y, agent.getSize() / 10, agent.getTiredness() * 100);
			if (agent.getToietNeed() > 0.0)
				hungerBarTexture.render(renderer, x + agent.getSize() + agent.getSize() / 10, y, agent.getSize() / 10, agent.getToietNeed() * 100);
		}
	}
	if (agent.characterType == "Player")
		characterTex.renderRotation(renderer, x, y, agent.getSize(), agent.getSize(), agent.rotation);


}