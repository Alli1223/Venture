#pragma once
#include "Player.h"
#include "Timer.h"
class GameSettings
{
public:
	GameSettings();
	~GameSettings();

	std::ofstream playerSave;
	

	void savePlayerSettings(Player& player);
	Player getPlayerFromSave();


	//! Calculate FPS
	void CalculateFramesPerSecond();
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };



	//Timer used to update the caption
	Timer fpsTimer;
	float getAverageFPS() { return avgFPS; }

	//In memory text stream
	std::stringstream timeText;



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

private:
	//The frames per second timer
	//Timer used to calculate the frames per second
	int frame = 0;
	//Start counting frames per second
	int countedFrames = 0;
	float avgFPS = 0;

};

