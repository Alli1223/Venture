#include "stdafx.h"
#include "SpaceGame.h"
#include "InitialisationError.h"

SpaceGame::SpaceGame() : backgroundTexture("Resources\\background5.jpg")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}
	gameSettings.getScreenResolution();
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
	window = SDL_CreateWindow("SpaceGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	
	if (window == nullptr)
	{
		throw InitialisationError("SDL_CreateWindow failed");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		throw InitialisationError("SDL_CreateRenderer failed");
	}

	
	
}

SpaceGame::~SpaceGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void SpaceGame::run()
{
	running = true;
	// Creates a grid of cells
	//level.makeGrid(WINDOW_WIDTH, WINDOW_HEIGHT);
	level.makeGrid(200, 200);
	terrainGen.populateTerrain(level);

	int cellSize = level.getCellSize();
	
	

	// If the client wants to connect to loopback address or external server
	if (networkManager.isServerLocal)
		networkManager.setServerIP(networkManager.InternalIPAddresss);
	else
		networkManager.setServerIP(networkManager.ExternalIPAddress);

	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());
	if (useNetworking)
	{
		networkManager.Connect();
		// Or Get player name
		if (networkManager.clientCanEnterName)
		{
			std::cout << "ENTER YOUR NAME: " << std::endl;
			std::cin >> playerName;
			std::cout << "NAME: " << playerName << std::endl;
		}

		// Send initial message with player name
		networkManager.sendTCPMessage(playerName + "\n");
		networkManager.RecieveMessage();
		networkManager.setPlayerName(playerName);
		std::cout << "PlayerName: " << playerName << std::endl;
	}
	else
	{
		Agent player;
		player.characterType = "Player";
		player.setID(playerName);
		player.setX(WINDOW_WIDTH / 2);
		player.setY(WINDOW_HEIGHT / 2);
		agentManager.SpawnAgent(player);
	}
	
	int oldPlayerX = 0, oldPlayerY = 0;
	//int xoffset = 0, yoffset = 0;
	camera.SetPos(0, 0);
	

	// values for the network update timer
	double lastTime = SDL_GetTicks();
	double timebehind = 0;
	bool runNetworkTick = false;
	/////////// MAIN LOOP /////////////////
	while (running)
	{
		// Interval Timer
		timebehind += SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();

		//Update intervalTimer
		while (timebehind >= networkManager.networkUpdateInterval)
		{
			runNetworkTick = true;
			timebehind -= networkManager.networkUpdateInterval;
		}

		runNetworkTick = true;
		// Update network
		if (runNetworkTick && useNetworking)
		{
			runNetworkTick = false;
			networkManager.NetworkUpdate(level, agentManager);
		}

		// Synchronse the network update thread
		//networkUpdateThread.join();
		input.HandleUserInput(level, agentManager, networkManager, camera, playerName, useNetworking, running);


		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			Item berry;
			berry.isBerry = true;
			agentManager.allAgents[0].inventory.add(berry);
			std::cout << agentManager.allAgents[0].inventory.getSize() << std::endl;
		}


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////



		for (int x = camera.getX() / cellSize; x < camera.getX() / cellSize + WINDOW_WIDTH / cellSize; x++)
		{
			for (int y = camera.getY() / cellSize; y < camera.getY() / cellSize + WINDOW_HEIGHT / cellSize; y++)
			{

				//Renders all he cells
				cellrenderer.RenderCells(level, renderer, x, y, camera.xoffset, camera.yoffset);


			} //End for Y loop
		}//End for X loop


		// Render characters
		agentManager.UpdateAgents(agentManager.allAgents, renderer, level);






		///////////////////////////////////////
		//MENU
		//////////////////////////////////////

		if (menu)
		{
			escapemenu.RunEscapeMenu(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, mouse_X, mouse_Y, running);
			running = false;
			if (escapemenu.exit)
			{
				running = false;
			}
			if (escapemenu.restart)
			{
			}
		}

		// Sync threads
		//if(networkUpdateThread.joinable())
			//networkUpdateThread.join();


		SDL_RenderPresent(renderer);
		// End while running
	}
	// Send quit message and close socket when game ends
	networkManager.sendTCPMessage("QUIT\n");
	networkManager.socket->close();
}


void SpaceGame::deleteVectors()
{
}

bool static isMouseOverRoomCell(Level& level)
{
	int mouse_X, mouse_Y;
	SDL_GetMouseState(&mouse_X, &mouse_Y);
	if (level.grid[mouse_X / level.getCellSize()][mouse_Y / level.getCellSize()]->isRoom)
	{
		return true;
	}
	else
	{
		return false;
	}
}