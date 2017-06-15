#pragma once
#include "Level.h"
#include "Camera.h"
#include "Character.h"
#include "Agent.h"

class CellRendering
{
public:
	CellRendering();
	~CellRendering();

	void RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, std::vector<Agent>& allAgents);

	void CellRendering::RenderChunk(Level& level, Camera& camera, Chunk& chunk, SDL_Renderer* renderer);

	void CellRendering::RenderAgents(Agent& agent, SDL_Renderer* renderer, Level& level, Camera& camera);

	bool renderStats = false;

private:
	const std::string RoomSpriteTextureLocation = "Resources\\Sprites\\roomSprites\\texturePack\\";
	const std::string ItemsSpriteTextureLocation = "Resources\\Sprites\\SpawnItems\\";
	const std::string TerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\";
	const std::string TreeTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\Trees\\";
	const std::string WallSpriteTextureLocation = "Resources\\Sprites\\Terrain\\Walls\\";

	const std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	const std::string playerStatsTextureLocation = "Resources\\Sprites\\GUI\\PlayerStats\\";

	// Textures for game objects
	//! For cells that are a room
	Texture roomCell;
	//! For cells that are transparent
	Texture emptyCell;
	//! For door cells
	
	//! Is the textures for the terrain
	Texture Grass1Texture;
	Texture Grass2Texture;
	Texture OakTreeTexture;
	Texture FernTreeTexture;

	Texture TreePixelTexture;
	Texture TreeTwoTexture;
	Texture TreeThreeTexture;
	Texture DirtTexture;
	Texture Flower1Texture;
	Texture Flower2Texture;
	Texture BerryPlantTexture;
	Texture BushTexture;
	Texture LongGrass1;
	Texture LongGrass2;
	Texture LongGrass3;


	Texture WaterTexture;
	Texture SandTexture;
	Texture StoneWallTexture;
	Texture SnowTexture;

	Texture WoodFenceSide;
	Texture WoodFenceUP;
	Texture WoodFenceCenter;

	//! Character Textures
	Texture characterTex;

	//! Are the textures for the NPC
	Texture npcDown;

	//! Are the textures for the statusbars
	Texture healthBarTexture;
	Texture hungerBarTexture;
	Texture tiredBarTexture;
	Texture oxygenBarTexture;
};

