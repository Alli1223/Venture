#include "stdafx.h"
#include "GameSettings.h"


GameSettings::GameSettings()
{
}


GameSettings::~GameSettings()
{
}

void GameSettings::getScreenResolution()
{

	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

		int should_be_zero = SDL_GetCurrentDisplayMode(i, &currentDisplay);

		if (should_be_zero != 0)
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

		else
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, currentDisplay.w, currentDisplay.h, currentDisplay.refresh_rate);
		break;
	}
	WINDOW_HEIGHT = currentDisplay.h;
	WINDOW_WIDTH = currentDisplay.w;

}

void GameSettings::savePlayerSettings(Player& player)
{
	json playerData;
	playerData["PlayerData"]["name"] = player.getID();
	playerData["PlayerData"]["rotation"] = player.getTargetRotation();
	playerData["PlayerData"]["X"] = player.getX();
	playerData["PlayerData"]["Y"] = player.getY();
	playerData["PlayerData"]["isMoving"] = player.isPlayerMoving();
	playerData["PlayerData"]["headWear"] = player.PlayerClothes.head;
	playerData["PlayerData"]["hairColour"] = player.PlayerClothes.hair;
	playerData["PlayerData"]["eyeColour"] = player.PlayerClothes.eyes;
	playerData["PlayerData"]["bodyWear"] = player.PlayerClothes.body;
	playerData["PlayerData"]["legWear"] = player.PlayerClothes.leg;
	playerSave.open("Resources\\SaveData\\playerData.txt");
	playerSave << playerData.dump();
	std::cout << "Saved Player settings." << std::endl;
	playerSave.close();
}

Player GameSettings::getPlayerFromSave()
{
	Player existingPlayer;
	std::string line;
	std::ifstream readPlayerSave("Resources\\SaveData\\playerData.txt");
	if (readPlayerSave.is_open())
	{
		while (std::getline(readPlayerSave, line))
		{
			//saveData = line;
			json jsonData = json::parse(line.begin(), line.end());;
			json playerData = jsonData.at("PlayerData");

				// Player movement
				int x = playerData.at("X").get<int>();
				//int y = element.at("Y").get<int>();
				//int rotation = element.at("rotation").get<int>();
				std::string name = playerData.at("name").get<std::string>();
				bool isMoving = playerData.at("isMoving").get<bool>();

				// Player clothes
				int headWear = playerData.at("headWear").get<int>();
				int hairColour = playerData.at("hairColour").get<int>();
				int eyeColour = playerData.at("eyeColour").get<int>();
				int bodyWear = playerData.at("bodyWear").get<int>();
				int legWear = playerData.at("legWear").get<int>();

				existingPlayer.PlayerClothes.head = (Player::Clothing::HeadWear)headWear;
				existingPlayer.PlayerClothes.hair = (Player::Clothing::HairColour)hairColour;
				existingPlayer.PlayerClothes.eyes = (Player::Clothing::EyeColour)eyeColour;
				existingPlayer.PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
				existingPlayer.PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
				existingPlayer.setPlayerMoving(isMoving);
				//existingPlayer.setX(x);
				//existingPlayer.setY(y);
				//existingPlayer.setTargetRotation(rotation);

			
		}
		
		readPlayerSave.close();
	}
	return existingPlayer;
	
}