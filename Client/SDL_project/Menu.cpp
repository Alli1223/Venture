#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(menuTextures + "Background.png")
{
}


Menu::~Menu()
{
}

void Menu::MainMenu(Player& player, Camera& camera, SDL_Renderer* renderer)
{

	while (displayMainMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}
		menuBackground.render(renderer, 0, 0, camera.WindowWidth, camera.WindowHeight);
		SDL_RenderPresent(renderer);
	}
	CharacterCustomisation(player);
}

void Menu::CharacterCustomisation(Player& player) 
{


}