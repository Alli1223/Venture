#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(menuTextures + "Background.png"), cursor(menuTextures + "Cursor.png")
{
}


Menu::~Menu()
{
}

void Menu::MainMenu(GameSettings& gameSettings, Player& player, SDL_Renderer* renderer)
{
	// Create buttons
	Button CharacterScreen("Character Customisation");
	Button Exit("Exit");

	// Scale mouse correctly depending on resolution
	menuCursorSize = gameSettings.WINDOW_WIDTH / 25;

	while (displayMainMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayMainMenu = false;
			}
		}
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);


		Exit.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, 100, 100);

		CharacterScreen.render(renderer, 500, 300, 300, 100);
		if (CharacterScreen.isPressed())
		{
			CharacterCustomisation(player);
		}
		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / menuCursorSize), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}	
}

void Menu::CharacterCustomisation(Player& player) 
{

}