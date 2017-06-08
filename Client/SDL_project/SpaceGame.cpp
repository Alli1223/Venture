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
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT / 2;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH / 2;
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
	camera.SetPos(0, 0);
	camera.WindowHeight = WINDOW_HEIGHT;
	camera.WindowWidth = WINDOW_WIDTH;

	level.GenerateWorld(camera);


	//terrainGen.populateTerrain(level);
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

		Agent player;
		player.characterType = "Player";
		player.setSpeed(5);
		player.setID(playerName);
		player.setX(WINDOW_WIDTH / 2);
		player.setY(WINDOW_HEIGHT / 2);
		agentManager.SpawnAgent(player);
	}
	else
	{
		Agent player;
		player.characterType = "Player";
		player.setSpeed(5);
		player.setID(playerName);
		player.setX(camera.WindowWidth / 2);
		player.setY(camera.WindowHeight / 2);
		agentManager.SpawnAgent(player);
	}

	// values for the network update timer
	double lastTime = SDL_GetTicks();
	double timebehind = 0;
	bool runNetworkTick = false;


	/////////// MAIN LOOP /////////////////
	while (running)
	{
		mouseCellPosition.x = mouse_X / cellSize;
		mouseCellPosition.y = mouse_Y / cellSize;


		
	

		// Interval Timer
		timebehind += SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();

		//Update intervalTimer
		while (timebehind >= networkManager.networkUpdateInterval)
		{
			runNetworkTick = true;
			timebehind -= networkManager.networkUpdateInterval;
		}
		// Update network
		if (runNetworkTick && useNetworking)
		{
			runNetworkTick = false;
			networkManager.NetworkUpdate(level, agentManager);
			//std::cout << level.tiles.size() << " " << level.tiles[0].size() << std::endl;
		}
		//terrainGen.GenerateTerrain(level, agentManager);
		
		// Synchronse the network update thread
		//networkUpdateThread.join();
		input.HandleUserInput(level, agentManager, networkManager, camera, playerName, useNetworking, running);



		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			//Item berry;
			//berry.isBerry = true;
			//agentManager.allAgents[0].inventory.add(berry);

			level.GetGlobalCell(camera, mouse_X / cellSize, mouse_Y / cellSize);
		}

		//Move player
		camera.setX(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX());
		camera.setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY());
		level.GenerateWorld(camera);

		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			//int x = level.GetGlobalCell(camera, mouse_X / cellSize, mouse_Y / cellSize).x;
			//int y = level.GetGlobalCell(camera, mouse_X / cellSize, mouse_Y / cellSize).y;
			//level.CreateChunk(x / level.getChunkSize(), y / level.getChunkSize());

			//level.SetGlobalCell(camera, mouse_X / cellSize, mouse_Y / cellSize);
			//level.SetGlobalCell(camera, x, y, mouseCellPosition);

		}


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////

				//Renders all he cells
		cellrenderer.RenderCells(level, renderer, camera);


		// Render characters
		agentManager.UpdateAgents(agentManager.allAgents, renderer, level, camera);



		//level.World[1][2].tiles[3][4]->isVegetation = true;
		//level.World[1][1].tiles[3][4]->isFlower1 = true;


		///////////////////////////////////////
		//MENU
		///////////////////////////////////////

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
	if (useNetworking)
	{
		// Send quit message and close socket when game ends
		networkManager.sendTCPMessage("QUIT\n");
		networkManager.socket->close();
	}
}


void SpaceGame::deleteVectors()
{
}

bool static isMouseOverRoomCell(Level& level)
{
	int mouse_X, mouse_Y;
	SDL_GetMouseState(&mouse_X, &mouse_Y);
	if (level.tiles[mouse_X / level.getCellSize()][mouse_Y / level.getCellSize()]->isRoom)
	{
		return true;
	}
	else
	{
		return false;
	}
}