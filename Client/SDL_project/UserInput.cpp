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
	// ACTION BAR
	if (state[SDL_SCANCODE_0])
		toolbar.setToolbarSelection(10);
	else if (state[SDL_SCANCODE_1])
		toolbar.setToolbarSelection(0);
	else if (state[SDL_SCANCODE_2])
		toolbar.setToolbarSelection(1);
	else if (state[SDL_SCANCODE_3])
		toolbar.setToolbarSelection(2);
	else if (state[SDL_SCANCODE_4])
		toolbar.setToolbarSelection(3);
	else if (state[SDL_SCANCODE_5])
		toolbar.setToolbarSelection(4);
	else if (state[SDL_SCANCODE_6])
		toolbar.setToolbarSelection(5);
	else if (state[SDL_SCANCODE_7])
		toolbar.setToolbarSelection(6);
	else if (state[SDL_SCANCODE_8])
		toolbar.setToolbarSelection(7);

	
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
	{
		level.setCellSize(level.getCellSize() + 1);
	}
		
	if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 1)
	{
		level.setCellSize(level.getCellSize() - 1);
	}
		

	if (state[SDL_SCANCODE_F10])
		level.setTimeOfDay(12.0);
	
	if (state[SDL_SCANCODE_F9])
		level.setTimeOfDay(7.0);

	// Use Action
	if (state[SDL_SCANCODE_F])
	{
		UseItemFromToolbar(toolbar, player, level, networkManager, gameSettings);
	}
	if (state[SDL_SCANCODE_M])
	{
		if(gameSettings.useNetworking)
			networkManager.MapNetworkUpdate(level);
	}
	if (state[SDL_SCANCODE_B])
	{

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

void UserInput::UseItemFromToolbar(ToolBar& toolbar, Player& player, Level& level, NetworkManager& networkManager, GameSettings& gameSettings)
{
	// AXE
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isAXE)
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

						Item wood;
						wood.type.Resource = Item::ItemType::isWOOD;
						player.inventory.add(wood);
					}
				}
			}
	}
	// HOE
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isHOE)
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
	// SCYTHE
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isSCYTHE)
	{
		if (level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isWheat)
		{
			if (level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->seedsStage == Cell::seedsGrowthStage::PlantStageFour)
			{
				Item wheat;
				wheat.type.Food = Item::ItemType::isWHEAT;
				player.inventory.add(wheat);
			}
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isWheat = false;
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->seedsStage = Cell::seedsGrowthStage::PlantStageZero;
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
	// Wheat SEEDS
	if (toolbar.getSelectedItem().type.Food == Item::ItemType::isSEEDS)
	{
		if (level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isDirt && !level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isWheat)
		{
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isWheat = true;
			level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->seedsStage = Cell::seedsGrowthStage::PlantStageOne;
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}

	// FISHING ROD
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isFISHINGROD)
	{
		if (level.getCell(player.getCellX() + 2, player.getCellY())->isWater)
		{
			level.getCell(player.getCellX() + 2, player.getCellY())->isWater = false;
		}
		/*
		if (level.getCell(player.getCellX() + 2, player.getCellY())->isWater)
		// Cast Line Right
		else if (level.getCell(player.getCellX() - 2, player.getCellY())->isWater)
			// Cast Line Left
		else if (level.getCell(player.getCellX(), player.getCellY() - 2)->isWater)
			// Cast line up
		else if (level.getCell(player.getCellX(), player.getCellY() + 2)->isWater)
			// Cast line down
			*/
	}
}