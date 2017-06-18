#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
}


UserInput::~UserInput()
{
}

bool UserInput::CheckIfCellIsWalkable(Level& level, int x, int y)
{

	int chunkX = (x / level.getCellSize()) / level.getChunkSize();
	int chunkY = (y / level.getCellSize()) / level.getChunkSize();

	int cellX = x / level.getCellSize() - (chunkX * level.getChunkSize());
	int cellY = y / level.getCellSize() - (chunkY * level.getChunkSize());

	if (cellX < 0)
	{
		cellX += level.getChunkSize();
		chunkX -= 1;
	}
	if (cellY < 0)
	{
		cellY += level.getChunkSize();
		chunkY -= 1;
	}

	if (!level.World[chunkX][chunkY].tiles[cellX][cellY]->isWalkable)
	{
		return false;
	}
	else
		return true;
}

void UserInput::HandleUserInput(Level& level, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, std::string playerName, bool useNetworking, bool& running)
{
	int cellSize = level.getCellSize();
	SDL_Event ev;
	if (SDL_PollEvent(&ev) != 0) {
		if (ev.type == SDL_QUIT) {
			running = false;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		running = false;

	int playerX = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX();
	int playerY = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY();
	int playerSpeed = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getSpeed();
	int agentNo = agentManager.GetAgentNumberFomID(playerName);
	playerChunkPos = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].chunkPos;
	playercellPos = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].cellPos;
	InterDir = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].cellInteractionDirection;

	/////////// PLAYER MOVEMENT ////////////
	//Diagonal movement
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		agentManager.allAgents[agentNo].targetRotation = 225;
		if(CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY - playerSpeed))
			agentManager.allAgents[agentNo].setPosition(playerX + playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		agentManager.allAgents[agentNo].targetRotation = 135;
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY - playerSpeed))
			agentManager.allAgents[agentNo].setPosition(playerX - playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		agentManager.allAgents[agentNo].targetRotation = -45;
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY + playerSpeed))
			agentManager.allAgents[agentNo].setPosition(playerX + playerSpeed, playerY + playerSpeed);

	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		agentManager.allAgents[agentNo].targetRotation = 45;
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY + playerSpeed))
			agentManager.allAgents[agentNo].setPosition(playerX - playerSpeed, playerY + playerSpeed);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		agentManager.allAgents[agentNo].targetRotation = 0;
		if (CheckIfCellIsWalkable(level, playerX, playerY + playerSpeed))
			agentManager.allAgents[agentNo].setY(playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_A])
	{
		agentManager.allAgents[agentNo].targetRotation = 90;
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY))
			agentManager.allAgents[agentNo].setX(playerX - playerSpeed);

	}
	else if (state[SDL_SCANCODE_D])
	{
		agentManager.allAgents[agentNo].targetRotation = 270;
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY))
			agentManager.allAgents[agentNo].setX(playerX + playerSpeed);
	}
	else if (state[SDL_SCANCODE_W])
	{
		agentManager.allAgents[agentNo].targetRotation = 180;
		if (CheckIfCellIsWalkable(level, playerX, playerY - playerSpeed))
			agentManager.allAgents[agentNo].setY(playerY - playerSpeed);
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CAMERA

	if (state[SDL_SCANCODE_RIGHT])
	{ }
	if (state[SDL_SCANCODE_DOWN])
	{ }
	if (state[SDL_SCANCODE_LEFT])
	{ }
	if (state[SDL_SCANCODE_UP])
	{ }

	// Set cell size
	if (state[SDL_SCANCODE_PAGEUP])
		level.setCellSize(level.getCellSize() + 1);
	if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 1)
		level.setCellSize(level.getCellSize() - 1);

	if (state[SDL_SCANCODE_SPACE])
	{
		level.setTimeOfDay(12);
	}
	if (state[SDL_SCANCODE_R])
		level.setTimeOfDay(4);
	if (state[SDL_SCANCODE_F])
	{
		if (level.isCellInChunk(playercellPos.x, playercellPos.y -1))
		{
			std::cout << playercellPos.x - InterDir.x << " " << playercellPos.y - InterDir.y << std::endl;
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y - 1]->isWoodFence = true;
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y - 1]->isWalkable = false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Player Actions
	else if (state[SDL_SCANCODE_B])
		networkManager.sendTCPMessage("PLACE_BED\n");
	else if (state[SDL_SCANCODE_C])
		networkManager.sendTCPMessage("PLACE_BOX\n");
}

void UserInput::ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type)
{
	//Check if cell is in bounds
	glm::vec2 chunkPos;
	glm::vec2 actionPos;




	/*
	for (int playerPosX = playerX - cellSize * 2; playerPosX < playerX + cellSize * 2; playerPosX += cellSize)
	{
		for (int playerPosY = playerY - cellSize * 2; playerPosY < playerY + cellSize * 2; playerPosY += cellSize)
		{
			// Calculate the positions around the player to account for changeing of chunks
			int x = playerX / cellSize;
			int y = playerY / cellSize;
			chunkPos.x = (playerPosX / cellSize) / level.getChunkSize();
			chunkPos.y = (playerPosY / cellSize) / level.getChunkSize();


			if (level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isTree)
			{
				Item item;
				item.isWOOD;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isTree = false;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isStoneWall = true;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isWalkable = true;
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].inventory.add(item);
			}
		}
	}
	*/
}