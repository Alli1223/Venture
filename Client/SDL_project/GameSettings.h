#pragma once
#include "Player.h"
class GameSettings
{
public:
	GameSettings();
	~GameSettings();

	std::ofstream playerSave;
	

	void savePlayerSettings(Player& player);
	Player getPlayerFromSave();

	//! int that will be used to control movement speed
	const int FRAME_RATE = 60;

	//! initial window settings
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;
	int amountOfWoodInTrees = 3;
	int amountOfStoneInRocks = 3;

	//! Whether the game is fullscreen
	bool fullscreen = false;
	bool displayMouse = false;
	int mousePointerSize = 25;

	glm::vec2 mouseCellPos;

	float UIScale = 1.0;

	//! Whether the game uses networking and false if singleplayer
	bool useNetworking = false;

	//! Whether the game is running or not
	bool running = true;
	//! stores screen resolution
	SDL_DisplayMode currentDisplay;
	void getScreenResolution();
};

