#pragma once
class GameSettings
{
public:
	GameSettings();
	~GameSettings();

	//! int that will be used to control movement speed
	const int FRAME_RATE = 60;

	//! initial window settings
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;

	bool fullscreen = false;

	//! Whether the game is running or not
	bool running = true;
	//! stores screen resolution
	SDL_DisplayMode currentDisplay;
	void getScreenResolution();
};

