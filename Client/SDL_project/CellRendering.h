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

	void RenderCells(Level& level, SDL_Renderer* renderer, Camera& camera, std::vector<Agent>& allAgents);

	void CellRendering::RenderChunk(Level& level, Camera& camera, Chunk& chunk, SDL_Renderer* renderer);

	void CellRendering::RenderAgents(Agent& agent, SDL_Renderer* renderer, Level& level, Camera& camera);

	bool renderStats = false;

private:
	const std::string RoomSpriteTextureLocation = "Resources\\roomSprites\\texturePack\\";
	const std::string ItemsSpriteTextureLocation = "Resources\\SpawnItems\\";
	const std::string TerrainSpriteTextureLocation = "Resources\\Terrain\\";
	const std::string TreeTerrainSpriteTextureLocation = "Resources\\Terrain\\Trees\\";

	const std::string characterTextureLocation = "Resources\\Character\\";
	const std::string playerStatsTextureLocation = "Resources\\GUI\\PlayerStats\\";

	// Textures for game objects
	//! For cells that are a room
	Texture roomCell;
	//! For cells that are transparent
	Texture emptyCell;
	//! For door cells
	Texture openDoorTexture;
	Texture closedDoorTexture;
	//! To show the oxygen level in a room
	Texture oxygenTex;
	//! To show oxygen tanks
	Texture oxygenTank;
	//! To show fireExtinguisher
	Texture healthPack;
	//! To show the character health
	Texture healthBar;
	//! Label for character health
	Texture healthText;
	//! To show the oxygen level
	Texture oxygenBar;
	//! Label for oxygen level
	Texture oxygenText;
	//! This will display when the player fails to win	
	Texture gameOver;
	//!will display over the background when the player fails to win
	Texture gameOverText;
	//! Is the texture for the win background
	Texture winTexture;
	//! Is the texture for the win text
	Texture winText;
	//! Is the texture for the goal
	Texture goalTexture;
	//! Is the texture for fire
	Texture fireTexture;
	//! Is the texture for the background
	Texture backgroundTexture;

	//! Is the texture for the cargoBay
	Texture cargoBayTexture;
	//! Is the texture for the cargo
	Texture cargoTexture;

	//! Is the texture for the beds
	Texture bedSideTexture;
	//! Is the texture for the toilet
	Texture toiletTexture;
	//! Is the texture for the kitchen
	Texture kitchenTexture;
	


	//! Is the textures for the terrain
	Texture Grass1Texture;
	Texture Grass2Texture;
	Texture OakTreeTexture;
	Texture FernTreeTexture;

	Texture PixelTexture;
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


	//! Is the texture for hull breaches
	Texture hullBreachTexture;
	//! Is the death animation texture
	Texture deathAnim;

	//! Are the textures for the differnt sides of the room cells
	Texture topRoomCell;
	Texture topRightRoomCell;
	Texture rightRoomCell;
	Texture bottomRightRoomCell;
	Texture bottomRoomCell;
	Texture bottomLeftRoomCell;
	Texture leftRoomCell;
	Texture topLeftRoomCell;


	//! Character Textures
	Texture characterTex;
	//! Is the textures for the default character
	Texture characterLeft;
	Texture characterRight;
	Texture characterUp;
	Texture characterDown;

	//! Are the textures for the NPC
	Texture npcLeft;
	Texture npcRight;
	Texture npcUp;
	Texture npcDown;

	//! Are the textures for the statusbars
	Texture healthBarTexture;
	Texture hungerBarTexture;
	Texture tiredBarTexture;
	Texture oxygenBarTexture;
};

