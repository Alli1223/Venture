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

void UserInput::HandleUserInput(Level& level, Player& player, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar)
{
	int cellSize = level.getCellSize();
	SDL_Event ev;
	if (SDL_PollEvent(&ev) != 0) 
	{
		if (ev.type == SDL_QUIT) 
		{
			gameSettings.running = false;
		}
		//Mouse wheel
		switch (ev.type)
		{
		case SDL_MOUSEWHEEL:
			if (ev.wheel.x < 0)
			{
				std::cout << "MOUSE : WHEEL LEFT" << std::endl;
			}
			else if (ev.wheel.x > 0)
			{
				std::cout << "MOUSE : WHEEL RIGHT" << std::endl;
			}
			if (ev.wheel.y < 0)
			{
				toolbar.setToolbarSelection(toolbar.getToolbarSelection() + 1);
			}
			else if (ev.wheel.y > 0)
			{
				toolbar.setToolbarSelection(toolbar.getToolbarSelection() - 1);
			}
			break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		gameSettings.running = false;

	
	int playerX = player.getX();
	int playerY = player.getY();
	int playerSpeed = player.getSpeed();
	int agentNo = agentManager.GetAgentNumberFomID(player.getID());
	playerChunkPos = player.chunkPos;
	playercellPos = player.cellPos;
	/////////// PLAYER MOVEMENT ////////////
	//Diagonal movement
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		//player.setTargetRotation(225);
		player.setTargetRotation(270);
		player.setPlayerMoving(true);
		if(CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY - playerSpeed))
			player.setPosition(playerX + playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		//player.setTargetRotation(135);
		player.setTargetRotation(90);
		player.setPlayerMoving(true);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY - playerSpeed))
			player.setPosition(playerX - playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(-45);
		player.setTargetRotation(270);
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY + playerSpeed))
			player.setPosition(playerX + playerSpeed, playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(45);
		player.setTargetRotation(90);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY + playerSpeed))
			player.setPosition(playerX - playerSpeed, playerY + playerSpeed);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(0);
		if (CheckIfCellIsWalkable(level, playerX, playerY + playerSpeed))
			player.setY(playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(90);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY))
			player.setX(playerX - playerSpeed);

	}
	else if (state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(270);
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY))
			player.setX(playerX + playerSpeed);
	}
	else if (state[SDL_SCANCODE_W])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(180);
		if (CheckIfCellIsWalkable(level, playerX, playerY - playerSpeed))
			player.setY(playerY - playerSpeed);
	}
	else
	{
		player.setSpeed(0);
		player.setPlayerMoving(false);
		player.setTargetRotation(0);
		//Reset the walk animation
		player.getWalkAnimation().setCurrentFrame(0);
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CAMERA
	
	if (state[SDL_SCANCODE_RIGHT])
	{ 
		toolbar.setToolbarSelection(toolbar.getToolbarSelection() + 1);
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		toolbar.createToolbar(player, gameSettings);
	}
	
	if (state[SDL_SCANCODE_LEFT])
	{
		toolbar.setToolbarSelection(toolbar.getToolbarSelection() - 1);
	}
	if (state[SDL_SCANCODE_UP])
	{
		std::cout << player.inventory.getSize() << " " << std::endl;
	}

	// Set cell size
	if (state[SDL_SCANCODE_PAGEUP])
		level.setCellSize(level.getCellSize() + 1);
	if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 1)
		level.setCellSize(level.getCellSize() - 1);

	if (state[SDL_SCANCODE_F10])
		level.setTimeOfDay(12.0);
	
	if (state[SDL_SCANCODE_F9])
		level.setTimeOfDay(7.0);

	// Use Action
	if (state[SDL_SCANCODE_F])
	{
		playerUseAction(toolbar, player, level, networkManager, gameSettings);
	}
	if (state[SDL_SCANCODE_M])
	{
		if(gameSettings.useNetworking)
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

void UserInput::playerUseAction(ToolBar& toolbar, Player& player, Level& level, NetworkManager& networkManager, GameSettings& gameSettings)
{
	if (toolbar.getToolbarSelection() == 0)
	{
		for (int x = -1; x < 1; x++)
			for (int y = -1; y < 1; y++)
			{
				InterDir.x = playercellPos.x + x;
				InterDir.y = playercellPos.y - y;
				if (InterDir.x > 0 && InterDir.x < level.getChunkSize() && InterDir.x > 0 && InterDir.y < level.getChunkSize())
				{
					if (level.World[playerChunkPos.x][playerChunkPos.y].tiles[InterDir.x][InterDir.y]->isTree)
					{
						//dump celldata of where the player has changed the cell
						level.World[playerChunkPos.x][playerChunkPos.y].tiles[InterDir.x][InterDir.y]->isTree = false;
						level.World[playerChunkPos.x][playerChunkPos.y].tiles[InterDir.x][InterDir.y]->isDirt = true;
						std::string seralisedData = level.World[playerChunkPos.x][playerChunkPos.y].tiles[InterDir.x][InterDir.y]->getCellData().dump();
						std::cout << seralisedData << std::endl;
						if (gameSettings.useNetworking)
							networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
					}
				}
			}
	}
	if (toolbar.getToolbarSelection() == 1)
	{
		if (!level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isDirt)
		{
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isDirt = true;
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
}