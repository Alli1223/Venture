#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(colourTextures + "Grey.png"), cursor(menuTextures + "Cursor.png"), rgb(colourTextures + "Spectrum.png"), rgbWheel(colourTextures + "rgbWheel.png")
{
}


Menu::~Menu()
{
}
Uint32 get_pixel_at(Uint32 * pixels, int x, int y, int w)
{
	return pixels[y * w + x];
}

std::shared_ptr<Button> get_instance(Button& n)
{
	return std::make_shared<Button>(n);
}


void Menu::MainMenu(GameSettings& gameSettings,Level& level, Camera& camera, Player& player, SDL_Renderer* renderer)
{
	// Create buttons
	Button characterScreen("Character Customisation");
	Button exit("Exit");
	Button useNetworking("Multiplayer");
	//std::shared_ptr<Button> button;
	Button fullscreen(" Fullscreen ", "wood");
	auto& toggleFullscreen = get_instance(fullscreen);
	Button loadFromSave("Load Save Game");
	Button play("Just Play");
	auto& justPlay = get_instance(play);
	
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
		menuBackground.alterTransparency(100);
		menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);

		
		int menuY = gameSettings.WINDOW_HEIGHT / 2;
		int menuX = gameSettings.WINDOW_WIDTH / 2;
		int menuSeperationDistance = 75;
		int buttonHeight = 50;
		int buttonWidth = 200;
		// Render buttons
		exit.render(renderer, 50, 25, 100, 50);

		justPlay->render(renderer, menuX, menuY - menuSeperationDistance * 2, buttonWidth, buttonHeight);
		if (justPlay->isPressed())
		{
			player = gameSettings.getPlayerFromSave();
			displayMainMenu = false;
		}

		loadFromSave.render(renderer, menuX, menuY - menuSeperationDistance, buttonWidth, buttonHeight);
		if (loadFromSave.isPressed())
		{
			gameSettings.loadGameFromSave(level);
			displayMainMenu = false;
		}
		toggleFullscreen->render(renderer, menuX, menuY, buttonWidth, buttonHeight);
		
		if (toggleFullscreen->isPressed())
		{
			if (gameSettings.fullscreen)
			{
				toggleFullscreen->setText("Windowed");
				gameSettings.fullscreen = false;
			}
			else
			{
				toggleFullscreen->setText("Fullscreen");
				gameSettings.fullscreen = true;
			}
			
		}
		
		useNetworking.render(renderer, menuX, menuY + menuSeperationDistance, buttonWidth, buttonHeight);
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
		characterScreen.render(renderer, menuX, menuY + menuSeperationDistance * 2, buttonWidth, buttonHeight);
		if (characterScreen.isPressed())
		{
			CharacterCustomisationMenu(gameSettings,camera, player, renderer);
		}
		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}	
}

void Menu::CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, SDL_Renderer* renderer)
{
	Button back("Back");
	Button play("Play");
	Button changeHead("Change Hair");
	Button changeBody("Change Body");
	Button changeLegs("Change Trousers");
	Button changeHairColour("Change Hair Colour");
	Button changeEyeColour("Change Eye Colour");
	Button randomiseAll("Random");
	Button startingProfession("Profession");
	
	Player playerCreation = gameSettings.getPlayerFromSave();

	playerCreation.PlayerClothes.leg = Player::Clothing::jeans;
	playerCreation.PlayerClothes.body = Player::Clothing::jacket;
	playerCreation.PlayerClothes.head = Player::Clothing::longHair;

	// Load player from file
	playerCreation = gameSettings.getPlayerFromSave();
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	
	while (displayCharacterMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			//getColourWheelvalue(renderer, mouseX, mouseY);
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
		changeBody.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY(), 100, 50);
		changeLegs.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() + 100, 100, 50);
		randomiseAll.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 150, 150, 50);
		startingProfession.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 200, 150, 50);
		changeHairColour.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 100, 150, 50);
		changeEyeColour.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 50, 150, 50);
		play.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT - 50, 100, 50);

		

		// Button functionality
		//Legs
		if (changeLegs.isPressed())
		{
			if (playerCreation.PlayerClothes.leg == Player::Clothing::noLeg)
				playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
			else if(playerCreation.PlayerClothes.leg == Player::Clothing::chinos)
				playerCreation.PlayerClothes.leg = Player::Clothing::jeans;
			else if (playerCreation.PlayerClothes.leg == Player::Clothing::jeans)
				playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
		}
		// Body
		if (changeBody.isPressed())
		{
			if (playerCreation.PlayerClothes.body == Player::Clothing::noShirt)
				playerCreation.PlayerClothes.body = Player::Clothing::jacket;
			else if (playerCreation.PlayerClothes.body == Player::Clothing::jacket)
				playerCreation.PlayerClothes.body = Player::Clothing::dress;
			else if (playerCreation.PlayerClothes.body == Player::Clothing::dress)
				playerCreation.PlayerClothes.body = Player::Clothing::jacket;
		}
		// Head
		if (changeHead.isPressed())
		{
			if (playerCreation.PlayerClothes.head == Player::Clothing::shortHair)
				playerCreation.PlayerClothes.head = Player::Clothing::longHair;
			else if (playerCreation.PlayerClothes.head == Player::Clothing::longHair)
				playerCreation.PlayerClothes.head = Player::Clothing::shortHair;
			else if (playerCreation.PlayerClothes.head == Player::Clothing::noHeadWear)
				playerCreation.PlayerClothes.head = Player::Clothing::shortHair;
		}
		// Hair colour
		if (changeHairColour.isPressed())
		{
			changeEyes = false;
			changeHair = true;
			if(showColourWheel == false)
				showColourWheel = true;
			else
				showColourWheel = false;
			
		}
		// Eye colour
		if (changeEyeColour.isPressed())
		{
			changeEyes = true;
			changeHair = false;
			if (showColourWheel == false)
				showColourWheel = true;
			else
				showColourWheel = false;
		}
		if(randomiseAll.isPressed())
		{
			playerCreation.setHairColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setEyeColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setJacketColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setJeansColour(rand() % 255, rand() % 255, rand() % 255);
		}
		if (startingProfession.isPressed())
		{

		}

		bool renderCursor = true;
		// Mouse controls rgb in relation to center of image


		//TODO: Refactor this mess to be a proper colour wheel
		if (showColourWheel)
		{
			int size = 250;
			rgb.render(renderer, playerCreation.getX() - size , playerCreation.getY() , size, size);
			

			int ccX = playerCreation.getX() - playerCreation.getSize();
			int ccY = playerCreation.getY() + 100;
			if (mouseX > playerCreation.getX() + size - (size * 2) -150  && mouseX < playerCreation.getX() - (size / 2))
			{
				if (mouseY > playerCreation.getY() - size/ 2 && mouseY < playerCreation.getY() + (size / 2))
				{

					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{

						int r = ccX - mouseX;
						int g = ccY + mouseY;
						int b = ccX + mouseX;
						if(changeHair)
							playerCreation.setHairColour(r, g, b);
						else if(changeEyes)
							playerCreation.setEyeColour(r, g, b);
					}
					renderCursor = false;
					cursor.render(renderer, mouseX, mouseY, 10, 20);
				}
			}
		}
		// Render player
		playerCreation.RenderPlayer(renderer, camera);

		//rgb.render(renderer, gameSettings.WINDOW_WIDTH - (gameSettings.WINDOW_WIDTH / 4), gameSettings.WINDOW_HEIGHT - (gameSettings.WINDOW_HEIGHT / 4), 100, 100);
		back.render(renderer, 100, 50, 100, 50);
		// Exit button
		if (back.isPressed())
		{
			displayCharacterMenu = false;
			return;
		}
		if (play.isPressed())
		{
			displayCharacterMenu = false;
			displayMainMenu = false;
		}

		//Render the mouse cursor last
		if(renderCursor)
			cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}
	

	 //Only copy over the customsiation stuff
	//playerCreation.setSize(100);
	player.PlayerClothes = playerCreation.PlayerClothes;
	player.setHairColour(playerCreation.gethairColour().r, playerCreation.gethairColour().g, playerCreation.gethairColour().b);
	player.setEyeColour(playerCreation.getEyeColour().r, playerCreation.getEyeColour().g, playerCreation.getEyeColour().b);
	player.setJacketColour(playerCreation.getJacketColour().r, playerCreation.getJacketColour().g, playerCreation.getJacketColour().b);
	player.setJeansColour(playerCreation.getJeansColour().r, playerCreation.getJeansColour().g, playerCreation.getJeansColour().b);
	
}

SDL_Color Menu::getColourWheelvalue(SDL_Renderer* renderer,int x, int y)
{
	
	SDL_Surface * img = IMG_Load("Resources\\Sprites\\Colours\\rgbWheel.png");
	//SDL_SetRenderTarget(renderer, rgbWheel.getTexture());

	//SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ABGR8888, pixels, pitch);
	SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, img->w, img->h);
	void * pixels;

	SDL_LockTexture(rgbWheel.getTexture(), &img->clip_rect, &pixels, &img->pitch);

	memcpy(pixels, img->pixels, img->w * img->h);

	Uint32 * upixels = (Uint32 *)pixels;

	// get or modify pixels

	SDL_UnlockTexture(rgbWheel.getTexture());




	Uint32 pixel = get_pixel_at(upixels, x, y, img->w);
	Uint8 * colors = (Uint8 *)pixel;
	SDL_Color returncolor = { colors[0],colors[1],colors[2] };

	return returncolor;
	//Uint32 * pixels;
	//Uint8 * rgb;
	//SDL_RenderReadPixels(renderer, NULL, 0, pixels, SDL_PIXELFORMAT_RGB444);
	//SDL_GetRGB(pixels[x*y], SDL_PIXELFORMAT_RGBA4444, &rgb[0], &rgb[1], &rgb[2])

}
