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
	WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT / 2;
	WINDOW_WIDTH = gameSettings.WINDOW_WIDTH / 2;
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

	// Generates the world around the camera position
	terrainGen.setSeed(5123);

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


		player.characterType = "Player";
		player.setSpeed(5);
		player.setID(playerName);
		player.setX(0);
		player.setY(0);
	}
	else
	{
		player.characterType = "Player";
		player.setSpeed(5);
		player.setID(playerName);
		player.setX(0);
		player.setY(0);
	}
	// Values for the network update timer
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

		// Update intervalTimer
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
		}

		// Handle the input
		input.HandleUserInput(level, player, agentManager, networkManager, camera, playerName, useNetworking, running);

		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}

		// Set camera to follow player and generate the world
		camera.setX(player.getX() - camera.WindowWidth / 2);
		camera.setY(player.getY() - camera.WindowHeight / 2);
		level.GenerateWorld(camera);


		// Right click
		if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{

		}


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////

		// Renders all the cells and players
		cellrenderer.RenderObjects(level, renderer, camera, player, agentManager.allAgents);

		// Update the position of the player
		player.Update(level);

		

		// update other characters positions
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