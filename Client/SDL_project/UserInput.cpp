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

void UserInput::HandleUserInput(Level& level, Player& player, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, std::string playerName, bool useNetworking, bool& running)
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

	int playerX = player.getX();
	int playerY = player.getY();
	int playerSpeed = player.getSpeed();
	int agentNo = agentManager.GetAgentNumberFomID(playerName);
	playerChunkPos = player.chunkPos;
	playercellPos = player.cellPos;

	/////////// PLAYER MOVEMENT ////////////
	//Diagonal movement
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		player.setTargetRotation(225);
		if(CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY - playerSpeed))
			player.setPosition(playerX + playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		player.setTargetRotation(135);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY - playerSpeed))
			player.setPosition(playerX - playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		player.setTargetRotation(-45);
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY + playerSpeed))
			player.setPosition(playerX + playerSpeed, playerY + playerSpeed);

	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		player.setTargetRotation(45);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY + playerSpeed))
			player.setPosition(playerX - playerSpeed, playerY + playerSpeed);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		player.setTargetRotation(0);
		if (CheckIfCellIsWalkable(level, playerX, playerY + playerSpeed))
			player.setY(playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_A])
	{
		player.setTargetRotation(90);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY))
			player.setX(playerX - playerSpeed);

	}
	else if (state[SDL_SCANCODE_D])
	{
		player.setTargetRotation(270);
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY))
			player.setX(playerX + playerSpeed);
	}
	else if (state[SDL_SCANCODE_W])
	{
		player.setTargetRotation(180);
		if (CheckIfCellIsWalkable(level, playerX, playerY - playerSpeed))
			player.setY(playerY - playerSpeed);
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

	if (state[SDL_SCANCODE_F10])
		level.setTimeOfDay(12.0);
	
	if (state[SDL_SCANCODE_F9])
		level.setTimeOfDay(7.0);

	if (state[SDL_SCANCODE_F])
	{

			std::cout << playercellPos.x - InterDir.x << " " << playercellPos.y - InterDir.y << std::endl;
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isDirt = true;
			//level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isWalkable = false;
			
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if(useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		
	}
	if (state[SDL_SCANCODE_M])
	{
		if(useNetworking)
			networkManager.MapNetworkUpdate(level);
	}
}


//TODO: Re Implement This.
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