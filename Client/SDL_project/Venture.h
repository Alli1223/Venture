#pragma once
#include "Texture.h"
#include "Level.h"
#include "Map.h"
#include "Point.h"
#include "Cell.h"
#include "Oxygen.h"
#include "Fire.h"
#include "AgentInteraction.h"
#include "PathFinder.h"
#include "GameSettings.h"
#include "GUI.h"
#include "ToolBar.h"
#include "Items.h"
#include "CellRendering.h"
#include "Agent.h"
#include "NetworkManager.h"
#include "NetworkClient.h"
#include "PerlinNoise.h"
#include "ProceduralTerrain.h"
#include "Camera.h"
#include "Inventory.h"
#include "UserInput.h"
#include "Player.h"
#include "TextUI.h"
#include "Menu.h"


//! The main class
/*!
This is the main class where the game is laoded and run. 
*/
class Venture
{
public:
	//! A constructor
	Venture();
	//! A deconstructor
	~Venture();

	//! Main Run loop
	void run();

	//! Removes all the data from stored vectors
	void Venture::deleteVectors();
	//! Initalising all classes needed for game
	Level level;
	GameSettings gameSettings;
	Map mapLoader;
	Oxygen oxygen;
	Fire fire;
	PlayerInteraction characterInteraction;
	AgentManager agentManager;
	Cell cell;
	ToolBar toolbar;
	CellRendering cellrenderer;
	NetworkManager networkManager;
	NetworkClient networkClient;
	ProceduralTerrain terrainGen;
	Camera camera;
	UserInput input;
	Player player;
	Menu menu;

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;

	//! The window width 
	int WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
	//! The window height
	int WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	//! Coordinates of the mouse 
	int mouse_X, mouse_Y;


	bool spawnPlayer = true;
	
	bool useNetworking = true;

	glm::vec2 mouseCellPosition;

	//! Whether the game is running or not
	bool running = true;
	//! Network update tick
	float timer;
private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Pointer to the window that the game will be rendered in
	SDL_Window* window;
	//" Pointer to the renderer
	SDL_Renderer* renderer;

	SDL_GLContext glContext;

	Texture backgroundTexture;

	//! Some colours for text output
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	
};

