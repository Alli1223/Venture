#pragma once

#include "Texture.h"
#include "Level.h"
#include "Map.h"
#include "Point.h"
#include "SDL2_image-2.0.1\include\SDL_image.h"
#include "Cell.h"
#include "Oxygen.h"
#include "Fire.h"
#include "RoomDesign.h"
#include "AgentInteraction.h"
#include "PathFinder.h"
#include "GameSettings.h"
#include "GUI.h"
#include "ToolBar.h"
#include "Items.h"
#include "EscapeMenu.h"
#include "DockingDoors.h"
#include "ShipManager.h"
#include "PlayerStats.h"
#include "CellRendering.h"
#include "Agent.h"
#include "NetworkManager.h"
#include "NetworkClient.h"
#include "PerlinNoise.h"
#include "ProceduralTerrain.h"
#include "Camera.h"
#include "Inventory.h"
#include "UserInput.h"

//! The main class
/*!
This is the main class where the game is laoded and run. 
*/
class SpaceGame
{
public:
	//! A constructor
	SpaceGame();
	//! A deconstructor
	~SpaceGame();

	//! Main Run loop
	void run();

	//! Removes all the data from stored vectors
	void SpaceGame::deleteVectors();
	//! Initalising all classes needed for game
	Level level;
	GameSettings gameSettings;
	Map mapLoader;
	RoomDesign designroom;
	Oxygen oxygen;
	Fire fire;
	PlayerInteraction characterInteraction;
	AgentManager agentManager;
	Cell cell;
	ToolBar toolbar;
	EscapeMenu escapemenu;
	DockingDoors dockingdoors;
	ShipManager shipmanager;
	PlayerStats playerstats;
	CellRendering cellrenderer;
	NetworkManager networkManager;
	NetworkClient networkClient;
	ProceduralTerrain terrainGen;
	Camera camera;
	UserInput input;

	


	//! Conains the list of nodes that makes the path
	//std::vector<Point> path;

	//! Contains a list of all the ship
	std::vector<Ship> allShips;

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;

	//! The window width 
	int WINDOW_WIDTH = gameSettings.WINDOW_WIDTH;
	//! The window height
	int WINDOW_HEIGHT = gameSettings.WINDOW_HEIGHT;
	//! Coordinates of the mouse 
	int mouse_X, mouse_Y;

	int cameraX = 0, cameraY = 0;

	bool spawnPlayer = true;
	
	bool useNetworking = true;
	

	//! Network update tick
	float timer;
private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Pointer to the window that the game will be rendered in
	SDL_Window* window;
	//" Pointer to the renderer
	SDL_Renderer* renderer;

	Texture backgroundTexture;

	//! Whether the game is running or not
	bool running;
	bool menu;
};

