#pragma once
#include "GUI.h"
#include "Icon.h"
#include "Texture.h"
class InventoryUI : public GUI
{
public:
	InventoryUI();
	~InventoryUI();
	void RenderInventory(SDL_Renderer* renderer, GameSettings& gameSettings, Player& player);
	void CreateInventory(SDL_Renderer* renderer, GameSettings& gameSettings, Player& player);
private:
	std::vector<std::shared_ptr<Icon>> inventoryIcons;
	Texture backgroundTexture;
	std::string iconTextureLocation = "Resources\\Sprites\\\Toolbar\\";
	bool displayInventory = true;
};

