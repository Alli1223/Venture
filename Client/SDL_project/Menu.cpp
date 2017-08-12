#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(colourTextures + "Grey.png"), cursor(menuTextures + "Cursor.png"), rgb(colourTextures + "Spectrum.png")
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
	Button changeHead("Change Head");
	Button changeBody("Change Body");
	Button changeLegs("Change Trousers");
	Button changeHairColour("Change Hair Colour");
	Button changeEyeColour("Change Eye Colour");
	
	
	Player playerCreation;
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
	playerCreation.PlayerClothes.body = Player::Clothing::jacket;
	playerCreation.PlayerClothes.hair = Player::Clothing::pinkHair;
	playerCreation.PlayerClothes.head = Player::Clothing::longHair;

	
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
		
		// Customisation buttons
		changeHead.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() - 100, 100, 50);
		changeBody.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() , 100, 50);
		changeLegs.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() + 100, 100, 50);
		changeHairColour.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 100, 150, 50);
		changeEyeColour.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 50, 150, 50);


		// Button functionality
		//Legs
		if (changeLegs.isPressed())
		{
			if(playerCreation.PlayerClothes.leg == Player::Clothing::chinos)
				playerCreation.PlayerClothes.leg = Player::Clothing::jeans;
			else if (playerCreation.PlayerClothes.leg == Player::Clothing::jeans)
				playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
		}
		// Body
		if (changeBody.isPressed())
		{
			if (playerCreation.PlayerClothes.body == Player::Clothing::jacket)
				playerCreation.PlayerClothes.body = Player::Clothing::tshirt;
			else if (playerCreation.PlayerClothes.body == Player::Clothing::tshirt)
				playerCreation.PlayerClothes.body = Player::Clothing::jacket;
		}
		// Head
		if (changeHead.isPressed())
		{
			if (playerCreation.PlayerClothes.head == Player::Clothing::shortHair)
				playerCreation.PlayerClothes.head = Player::Clothing::longHair;
			else if (playerCreation.PlayerClothes.head == Player::Clothing::longHair)
				playerCreation.PlayerClothes.head = Player::Clothing::shortHair;
		}
		// Hair colour
		if (changeHairColour.isPressed())
		{
			if (playerCreation.PlayerClothes.hair == Player::Clothing::brownHair)
				playerCreation.PlayerClothes.hair = Player::Clothing::pinkHair;
			else if (playerCreation.PlayerClothes.hair == Player::Clothing::pinkHair)
				playerCreation.PlayerClothes.hair = Player::Clothing::brownHair;
		}
		// Eye colour
		if (changeEyeColour.isPressed())
		{
			if (playerCreation.PlayerClothes.eyes == Player::Clothing::brownEye)
				playerCreation.PlayerClothes.eyes = Player::Clothing::blueEye;
			else if (playerCreation.PlayerClothes.eyes == Player::Clothing::blueEye)
				playerCreation.PlayerClothes.eyes = Player::Clothing::brownEye;
		}
		
		// Render player
		playerCreation.RenderPlayer(renderer, false);

		//rgb.render(renderer, gameSettings.WINDOW_WIDTH - (gameSettings.WINDOW_WIDTH / 4), gameSettings.WINDOW_HEIGHT - (gameSettings.WINDOW_HEIGHT / 4), 100, 100);
		exit.render(renderer, 50, 25, 100, 50);
		// Exit button
		if (exit.isPressed())
		{
			//gameSettings.running = false;
			displayCharacterMenu = false;
			displayMainMenu = false;
		}



		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / menuCursorSize), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}
	//playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	playerCreation.setSize(50);
	player.PlayerClothes = playerCreation.PlayerClothes;

}