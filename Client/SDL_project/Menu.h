#pragma once
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
#include "Button.h"
#include "GameSettings.h"
class Menu
{
public:
	Menu();
	~Menu();

	void MainMenu(GameSettings& gameSettings, Player& player, SDL_Renderer* renderer);

	void CharacterCustomisation(Player& player);

	int setCursorSize(int newCursorSize) { return menuCursorSize = newCursorSize; }
private:
	bool displayMainMenu = true;
	std::string menuTextures = "Resources\\Sprites\\Menu\\";

	int mouseX, mouseY;
	int menuCursorSize = 30;

	

	//! Stores the menus background texture
	Texture menuBackground;

	Texture cursor;
};

