#pragma once
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
class Menu
{
public:
	Menu();
	~Menu();

	void MainMenu(Player& player, Camera& camera, SDL_Renderer* renderer);

	void CharacterCustomisation(Player& player);
private:
	bool displayMainMenu = true;
	std::string menuTextures = "Resources\\Sprites\\Menu\\";

	int mouseX, mouseY;
	

	//! Stores the menus background texture
	Texture menuBackground;
};

