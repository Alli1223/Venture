#include "stdafx.h"
#include "GameSettings.h"


GameSettings::GameSettings()
{
	//Calculate and correct fps
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

void GameSettings::CalculateFramesPerSecond()
{
	avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	std::cout << avgFPS << std::endl;
	countedFrames++;

}


//TODO: Create a mapdata json file for singleplayer
void GameSettings::savePlayerSettings(Player& player)
{
	
	json playerData;
	playerData["PlayerData"]["name"] = player.getID();
	playerData["PlayerData"]["rotation"] = player.getTargetRotation();
	playerData["PlayerData"]["X"] = player.getX();
	playerData["PlayerData"]["Y"] = player.getY();
	playerData["PlayerData"]["isMoving"] = player.isPlayerMoving();
	playerData["PlayerData"]["headWear"] = player.PlayerClothes.head;
	playerData["PlayerData"]["hairColour"]["r"] = player.gethairColour().r;
	playerData["PlayerData"]["hairColour"]["g"] = player.gethairColour().g;
	playerData["PlayerData"]["hairColour"]["b"] = player.gethairColour().b;
	playerData["PlayerData"]["eyeColour"]["r"] = player.getEyeColour().r;
	playerData["PlayerData"]["eyeColour"]["g"] = player.getEyeColour().g;
	playerData["PlayerData"]["eyeColour"]["b"] = player.getEyeColour().b;
	playerData["PlayerData"]["bodyWear"] = player.PlayerClothes.body;
	playerData["PlayerData"]["legWear"] = player.PlayerClothes.leg;
	playerSave.open(playerSavePath);
	playerSave << playerData.dump();
	std::cout << "Saved Player settings." << std::endl;
	playerSave.close();
}

void GameSettings::saveLevelData(Level& level)
{
	json levelData;
	json array;
	
	std::cout << "Level Saving.." << std::endl;
	//TODO: calculate explored area
	for (int x = level.xMinExplored; x < level.xMaxExplored; x++)
	{
		for (int y = level.yMinExplored; y < level.yMaxExplored; y++)
		{
			std::cout << x << " out of " << level.xMaxExplored << std::endl;
			array.push_back(level.getCell(x, y)->getCellData());
		}
	}
	levelData["Level"] = array;

	levelSave.open(levelSavePath);
	levelSave << levelData.dump();
	std::cout << "Level Saved." << std::endl;
	levelSave.close();
}

//TODO: Load game from save
Level GameSettings::loadGameFromSave(Level& level)
{
	Level levelToReturn;
	std::string line;
	std::ifstream readGameSave(levelSavePath);
	if (readGameSave.is_open())
	{
		while (std::getline(readGameSave, line))
		{
			json jsonData = json::parse(line.begin(), line.end());;

			json mapData = jsonData.at("Level");

			// Range-based for loop to iterate through the map data
			for (auto& element : mapData)
			{
				Cell nc;
				

				int x = element.at("X").get<int>();
				int y = element.at("Y").get<int>();
				nc.setPos(x, y);

				int plantGrowthStage;

				if (element.count("Grass") > 0)
					nc.isGrass = element.at("Grass").get<bool>();
				if (element.count("Water") > 0)
					nc.isWater = element.at("Water").get<bool>();
				if (element.count("Sand") > 0)
					nc.isSand = element.at("Sand").get<bool>();
				if (element.count("Fence") > 0)
					nc.isWoodFence = element.at("Fence").get<bool>();
				if (element.count("Dirt")  > 0)
					nc.isDirt = element.at("Dirt").get<bool>();
				if (element.count("Wheat")  > 0)
					nc.isWheat = element.at("Wheat").get<bool>();
				if (element.count("Wood")  > 0)
					nc.isWood = element.at("Wood").get<bool>();
				if (element.count("Stone")  > 0)
					nc.isStone = element.at("Stone").get<bool>();
				if (element.count("StoneWall")  > 0)
					nc.isStoneWall = element.at("StoneWall").get<bool>();
				if (element.count("PlantStage")  > 0)
					plantGrowthStage = element.at("PlantStage").get<int>();

				level.SetCell(x, y, nc);
			}
		}
	}


	return levelToReturn;
}


Player GameSettings::getPlayerFromSave()
{
	Player existingPlayer;
	std::string line;
	std::ifstream readPlayerSave(playerSavePath);
	if (readPlayerSave.is_open())
	{
		while (std::getline(readPlayerSave, line))
		{
			//saveData = line;
			json jsonData = json::parse(line.begin(), line.end());;
			json playerData = jsonData.at("PlayerData");

				// Player movement
				int x = playerData.at("X").get<int>();
				int y = playerData.at("Y").get<int>();
				int rotation = playerData.at("rotation").get<int>();
				std::string name = playerData.at("name").get<std::string>();
				bool isMoving = playerData.at("isMoving").get<bool>();

				// Player clothes
				int headWear = playerData.at("headWear").get<int>();
				int bodyWear = playerData.at("bodyWear").get<int>();
				int legWear = playerData.at("legWear").get<int>();


				json hairColour = playerData.at("hairColour");
				int hr = hairColour.at("r").get<int>();
				int hg = hairColour.at("g").get<int>();
				int hb = hairColour.at("b").get<int>();
				json eyeColour = playerData.at("eyeColour");
				int er = eyeColour.at("r").get<int>();
				int eg = eyeColour.at("g").get<int>();
				int eb = eyeColour.at("b").get<int>();

				existingPlayer.setEyeColour(er, eg, eb);
				existingPlayer.setHairColour(hr, hg, hb);

				existingPlayer.PlayerClothes.head = (Player::Clothing::HeadWear)headWear;
				existingPlayer.PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
				existingPlayer.PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
				existingPlayer.setPlayerMoving(isMoving);
		}
		
		readPlayerSave.close();
	}
	return existingPlayer;
}