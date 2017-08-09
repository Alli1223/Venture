#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(colourTextures + "Grey.png"), cursor(menuTextures + "Cursor.png")
{
}


Menu::~Menu()
{
}

void Menu::MainMenu(GameSettings& gameSettings, Player& player, SDL_Renderer* renderer)
{
	// Create buttons
	Button characterScreen("Character Customisation");
	Button exit("Exit");
	Button useNetworking("Multiplayer");

	// Scale mouse correctly depending on resolution
	menuCursorSize = gameSettings.WINDOW_WIDTH / 25;

	// Display the menu screen
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



		// Render buttons
		exit.render(renderer, 50, 25, 100, 50);
		useNetworking.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, 400, 100);
		if (useNetworking.isPressed())
		{
			//TODO: add delay to button so it's easier to change the setting
			if (gameSettings.useNetworking == true)
			{
				gameSettings.useNetworking = false;
				useNetworking.setText("SinglePlayer");
			}
			else
			{
				gameSettings.useNetworking = true;
				useNetworking.setText("Multiplayer");
			}
		}


		// IF exit is pressed
		if (exit.isPressed())
		{
			gameSettings.running = false;
			displayMainMenu = false;
		}


		// Character Screen
		characterScreen.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 4, 400, 100);
		if (characterScreen.isPressed())
		{
			CharacterCustomisationMenu(gameSettings, player, renderer);
		}
		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}	
}

void Menu::CharacterCustomisationMenu(GameSettings& gameSettings, Player& player, SDL_Renderer* renderer)
{
	Button exit("Exit");
	Button changeLegs("Change Trousers");

	Player playerCreation;
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	playerCreation.PlayerClothes.leg = Player::Clothing::chinos;

	
	int legCycle = 0;
	while (displayCharacterMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayCharacterMenu = false;
			}
		}
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);
		
		
		changeLegs.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY(), 100, 50);
		

		if (changeLegs.isPressed())
		{
			
			if(playerCreation.PlayerClothes.leg == Player::Clothing::chinos)
				playerCreation.PlayerClothes.leg = Player::Clothing::jeans;
			else if (playerCreation.PlayerClothes.leg == Player::Clothing::jeans)
				playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
		}
		
		
		
		playerCreation.RenderPlayer(renderer);

		exit.render(renderer, 50, 25, 100, 50);
		if (exit.isPressed())
		{
			gameSettings.running = false;
			displayCharacterMenu = false;
			displayMainMenu = false;
		}



		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / menuCursorSize), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}
	player = playerCreation;
}