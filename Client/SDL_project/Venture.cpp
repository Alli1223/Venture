#include "stdafx.h"
#include "Venture.h"
#include "InitialisationError.h"
void showErrorMessage(const char* message, const char* title)
{
	// Note: this is specific to Windows, and would need redefining to work on Mac or Linux
	MessageBoxA(nullptr, message, title, MB_OK | MB_ICONERROR);
}

bool compileShader(GLuint shaderId, const std::string& shaderFileName)
{
	// Read the source code from the file
	std::string shaderSource;
	std::ifstream sourceStream(shaderFileName, std::ios::in);
	if (sourceStream.is_open())
	{
		std::stringstream buffer;
		buffer << sourceStream.rdbuf();
		shaderSource = buffer.str();
		sourceStream.close();
	}
	else
	{
		showErrorMessage(shaderFileName.c_str(), "File not found");
		return false;
	}

	// Compile the shader
	const char* sourcePointer = shaderSource.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	// Check the results of compilation
	GLint result = GL_FALSE;
	int infoLogLength = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1)
	{
		// Display the compilation log
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderId, infoLogLength, NULL, errorMessage.data());
		showErrorMessage(errorMessage.data(), shaderFileName.c_str());
	}

	return (result != GL_FALSE);
}

GLuint loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path) {

	// Create the shaders
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertexShaderId, vertex_file_path);

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragmentShaderId, fragment_file_path);

	// Link the program
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	// Check the program
	GLint result = GL_FALSE;
	int infoLogLength = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, errorMessage.data());
		showErrorMessage(errorMessage.data(), "glLinkProgram error");
	}

	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}


Venture::Venture() : backgroundTexture("Resources\\background5.jpg")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_TIMER) < 0)
	{
		throw InitialisationError("SDL_Init failed");
	}
	
	gameSettings.getScreenResolution();
	gameSettings.WINDOW_HEIGHT /= 2;
	gameSettings.WINDOW_WIDTH /= 2;
	camera.WindowHeight = gameSettings.WINDOW_HEIGHT;
	camera.WindowWidth = gameSettings.WINDOW_WIDTH;
	camera.SetPos(0, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("Venture", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);
	if (window == nullptr)
	{
		throw InitialisationError("SDL_CreateWindow failed");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		throw InitialisationError("SDL_CreateRenderer failed");
	}

	if (glewInit() != GLEW_OK)
	{
		showErrorMessage("glewInit failed", ":(");
	}

	// IF TTF Init error
	if (!TTF_WasInit() && TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
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
	// Run the main menu
	//menu.MainMenu(gameSettings, camera, player, renderer);

	// Add starting items
	Item hoe;
	hoe.type.Tool = Item::ItemType::isHOE;
	Item Axe;
	Axe.type.Tool = Item::ItemType::isAXE;
	Item seeds;
	seeds.type.Food = Item::ItemType::isSEEDS;

	player.inventory.add(Axe);
	player.inventory.add(hoe);
	player.inventory.add(seeds);


	// Generates the world around the camera position
	terrainGen.setSeed(4123);

	level.GenerateWorld(camera);

	int cellSize = level.getCellSize();

	// If the client wants to connect to loopback address or external server
	if (networkManager.isServerLocal)
		networkManager.setServerIP(networkManager.InternalIPAddress);
	else
		networkManager.setServerIP(networkManager.ExternalIPAddress);

	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());
	if (gameSettings.useNetworking)
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
	toolbar.createToolbar(player, gameSettings);
	/////////////////////////////////////////////// MAIN LOOP ///////////////////////////////////////
	while (gameSettings.running)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			
		}
		// Do all the networking
		if (gameSettings.useNetworking)
			networkManager.NetworkUpdate(level, player, agentManager);
		
		// Handle the input
		input.HandleUserInput(level, player, agentManager, networkManager, camera, gameSettings, toolbar);

		
		// Set camera to follow player and generate the world
		camera.setX(player.getX() - camera.WindowWidth / 2);
		camera.setY(player.getY() - camera.WindowHeight / 2);
		level.GenerateWorld(camera);

		// Clear Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Update the position of the player
		player.Update(level);

		// update other characters positions
		agentManager.UpdateAgents(agentManager.allAgents, renderer, level, camera);

		// Renders all the cells and players
		cellrenderer.RenderObjects(level, renderer, camera, player, agentManager.allAgents, networkManager.allPlayers);

		toolbar.Update(player, gameSettings);
		toolbar.RenderToolbar(renderer, gameSettings);
		SDL_RenderPresent(renderer);
		// End while running
	}
	gameSettings.savePlayerSettings(player);
	if (gameSettings.useNetworking)
	{
		// Send quit message and close socket when game ends
		networkManager.sendTCPMessage("QUIT\n");
		networkManager.socket->close();
	}
}