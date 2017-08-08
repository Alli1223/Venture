#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(menuTextures + "Background.png"), button("test"), cursor(menuTextures + "Cursor.png")
{
}


Menu::~Menu()
{
}

void Menu::MainMenu(Player& player, Camera& camera, SDL_Renderer* renderer)
{

	while (displayMainMenu)
	{
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayMainMenu = false;
			}
		}
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		menuBackground.render(renderer, camera.WindowWidth / 2, camera.WindowHeight / 2, camera.WindowWidth, camera.WindowHeight);

		button.setText("what");
		button.render(renderer, 100, 200, 100, 100);

		if (SDL_GetMouseState(&mouseX, &mouseY))
		{
			
		}


		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / menuCursorSize), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}
	CharacterCustomisation(player);
}

void Menu::CharacterCustomisation(Player& player) 
{


}