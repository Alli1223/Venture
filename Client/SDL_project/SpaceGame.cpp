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
	level.makeGrid(300, 300);
	terrainGen.populateTerrain(level);

	int cellSize = level.getCellSize();
	
	

	// If the client wants to connect to loopback address or external server
	if (networkManager.isServerLocal)
		networkManager.setServerIP(networkManager.InternalIPAddresss);
	else
		networkManager.setServerIP(networkManager.ExternalIPAddress);

	// Create socket and io service then connect to sever
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(networkManager.getServerIP()), networkManager.port);
	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());
	if (useNetworking)
	{
		socket.connect(endpoint);




		// Or Get player name
		if (networkManager.clientCanEnterName)
		{
			std::cout << "ENTER YOUR NAME: " << std::endl;
			std::cin >> playerName;
			std::cout << "NAME: " << playerName << std::endl;
		}


		// Send initial message with player name
		networkManager.sendTCPMessage(playerName + "\n", socket);
		networkManager.RecieveMessage(socket);
		networkManager.setPlayerName(playerName);
		std::cout << "PlayerName: " << playerName << std::endl;
	}
	else
	{
		Agent player;
		player.characterType = "Player";
		player.setX(WINDOW_WIDTH / 2);
		player.setY(WINDOW_HEIGHT / 2);
		agentManager.SpawnAgent(player);
	}
	
	int oldPlayerX = 0, oldPlayerY = 0;
	int xoffset = 0, yoffset = 0;
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


		// Update network
		if (runNetworkTick && useNetworking)
		{
			runNetworkTick = false;
			networkManager.NetworkUpdate(level, agentManager, socket);
		}


		// Synchronse the network update thread
		//networkUpdateThread.join();
		// Handle events
		SDL_Event ev;
		if (SDL_PollEvent(&ev))
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			switch (ev.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
			if (state[SDL_SCANCODE_ESCAPE] && menu == false)
			{
				menu = true;
			}
			else if (state[SDL_SCANCODE_ESCAPE] && menu == true)
				menu = false;

			//Pathfinding
			if (false)
			{
				if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					Agent NPC;
					NPC.characterType = "NPC";
					NPC.setX(mouse_X);
					NPC.setY(mouse_Y);
					//NPC.agentWonderWhenIdle = true;
					NPC.setID("TEST");
					agentManager.SpawnAgent(NPC);
					std::cout << "spawningAgent\n";
				}

				if (SDL_GetMouseState(&mouse_X, &mouse_Y) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					Point endpoint(mouse_X / cellSize, mouse_Y / cellSize);
					Point agentPoint(agentManager.allAgents[agentManager.GetAgentNumberFomID("TEST")].getX() / cellSize, agentManager.allAgents[agentManager.GetAgentNumberFomID("TEST")].getY() / cellSize);

					agentManager.allAgents[agentManager.GetAgentNumberFomID("TEST")].Move(level, agentPoint, endpoint);
				}
			}

			// Player Movement
			if (state[SDL_SCANCODE_S])
			{
				agentManager.allAgents[0].setY(agentManager.allAgents[0].getY() + agentManager.allAgents[0].getSpeed());
				agentManager.allAgents[0].agentRotation = 0;
				networkManager.sendTCPMessage("MOVE_SOUTH\n", socket);

			}
			if (state[SDL_SCANCODE_A])
			{
				agentManager.allAgents[0].setX(agentManager.allAgents[0].getX() - agentManager.allAgents[0].getSpeed());
				agentManager.allAgents[0].agentRotation = 90;
				networkManager.sendTCPMessage("MOVE_WEST\n", socket);
				//xoffset--;
			}
			if (state[SDL_SCANCODE_D])
			{
				agentManager.allAgents[0].setX(agentManager.allAgents[0].getX() + agentManager.allAgents[0].getSpeed());
				agentManager.allAgents[0].agentRotation = 270;
				networkManager.sendTCPMessage("MOVE_EAST\n", socket);
				//xoffset++;
			}
			if (state[SDL_SCANCODE_W])
			{
				agentManager.allAgents[0].agentRotation = 180;
				agentManager.allAgents[0].setY(agentManager.allAgents[0].getY() - agentManager.allAgents[0].getSpeed());
				networkManager.sendTCPMessage("MOVE_NORTH\n", socket);
				//yoffset--;
			}

			//Set offset to camera
			if (state[SDL_SCANCODE_RIGHT])
			{
				xoffset++;
				agentManager.allAgents[0].setOffsetX(-xoffset * cellSize);
				
			}
			if (state[SDL_SCANCODE_DOWN])
			{
				yoffset++;
				agentManager.allAgents[0].setOffsetY(-yoffset * cellSize);
				
			}
			if (state[SDL_SCANCODE_LEFT])
			{
				xoffset--;
				agentManager.allAgents[0].setOffsetX(-xoffset * cellSize);
				
			}
			if (state[SDL_SCANCODE_UP])
			{
				yoffset--;
				agentManager.allAgents[0].setOffsetY(-yoffset * cellSize);
				
			}


			// Player Actions
			else if (state[SDL_SCANCODE_B])
				networkManager.sendTCPMessage("PLACE_BED\n", socket);
			else if (state[SDL_SCANCODE_C])
				networkManager.sendTCPMessage("PLACE_BOX\n", socket);
			if (state[SDL_SCANCODE_G])
			{
				camera.SetPos(agentManager.allAgents[0].getX() - WINDOW_WIDTH / 2, agentManager.allAgents[0].getY() - WINDOW_HEIGHT / 2);
			}
				


		}//End pollevent if


		// Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Renders the background image
		backgroundTexture.render(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);

		int playerX = 0;
		int playerY = 0;
		if (agentManager.allAgents.size() >= 1)
		{
			playerX = agentManager.allAgents[0].getX() / cellSize;
			playerY = agentManager.allAgents[0].getY() / cellSize;
		}
		
		
		
		
		//////////////////////////////////
		//MAIN CELL LOOP
		///////////////////////////////////



		for (int x = camera.GetX() / cellSize; x < camera.GetX() / cellSize + WINDOW_WIDTH / cellSize; x++)
		{
			for (int y = camera.GetY() / cellSize; y < camera.GetY() / cellSize + WINDOW_HEIGHT / cellSize; y++)
			{

				//Renders all he cells
				cellrenderer.RenderCells(level, renderer, x, y, xoffset, yoffset);


			} //End for Y loop
		}//End for X loop
		

		std::cout << playerX << std::endl;


		//Right
		if (playerX > oldPlayerX)
		{
			//agentManager.allAgents[0].setX(playerX - 1 * cellSize );
			oldPlayerX = playerX;
			//xoffset++;
		}
		//Down
		else if (playerY > oldPlayerY)
		{
			oldPlayerY = playerY;
			//yoffset++;
		}
		//Left
		else if (playerX < oldPlayerX)
		{
			oldPlayerX = playerX;
			//xoffset--;
		}
		//Up
		else if (playerY < oldPlayerY)
		{
			oldPlayerY = playerY;
			//yoffset--;
		}
		
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
				socket.close();
				socket.connect(endpoint);
			}
		}

		// Sync threads
		//if(networkUpdateThread.joinable())
			//networkUpdateThread.join();


		SDL_RenderPresent(renderer);
	}// End while running

	// Send quit message and close socket when game ends
	networkManager.sendTCPMessage("QUIT\n", socket);
	socket.close();

}


void SpaceGame::deleteVectors()
{
	allHydroponicsFarms.erase(allHydroponicsFarms.begin(), allHydroponicsFarms.end());
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