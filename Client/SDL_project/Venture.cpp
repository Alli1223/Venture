#include "stdafx.h"
#include "Venture.h"
#include "InitialisationError.h"

Venture::Venture() : backgroundTexture("Resources\\background5.jpg")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}
	gameSettings.getScreenResolution();
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT ;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH ;
	camera.WindowHeight = WINDOW_HEIGHT;
	camera.WindowWidth = WINDOW_WIDTH;
	camera.SetPos(0, 0);
	window = SDL_CreateWindow("Venture", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	
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

Venture::~Venture()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Venture::run()
{

	//Generates the world around the camera position
	terrainGen.setSeed(1500);

	level.GenerateWorld(camera);


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
		player.setX(0);
		player.setY(0);
		agentManager.SpawnAgent(player);
	}
	else
	{
		Agent player;
		player.characterType = "Player";
		player.setSpeed(5);
		player.setID(playerName);
		player.setX(0);
		player.setY(0);
		agentManager.SpawnAgent(player);
	}
	//camera.SetPos(player.getX())

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

		//Set camera to follow player and generate the world
		camera.setX(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getX() - camera.WindowWidth / 2);
		camera.setY(agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].getY() - camera.WindowHeight / 2);

		level.GenerateWorld(camera);

		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			glm::vec2 playerChunkPos = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].chunkPos;
			glm::vec2 playercellPos = agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].cellPos;
			
			if (level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isGrass)
			{									   
				level.World[playerChunkPos.x][playerChunkPos.y].tiles[playercellPos.x][playercellPos.y]->isBush = true;
			}
			std::cout << playerChunkPos.x << " " << playerChunkPos.y << " | " << playercellPos.x << " " << playercellPos.y << std::endl;
		}


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////

				//Renders all he cells
		cellrenderer.RenderObjects(level, renderer, camera, agentManager.allAgents);


		// Render characters
		agentManager.UpdateAgents(agentManager.allAgents, renderer, level, camera);


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


void Venture::deleteVectors()
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