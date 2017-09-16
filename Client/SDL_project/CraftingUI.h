#pragma once
#include "GUI.h"
#include "Button.h"
#include "Inventory.h"
#include "Icon.h"
class CraftingUI :
	public GUI
{
public:
	CraftingUI();
	~CraftingUI();
	int getIconSize() { return craftingIconSize; }
	int setIconSize(int newSize) { return craftingIconSize = newSize; }
	void renderCraftingMenu(SDL_Renderer* renderer, Inventory& playerInventory);
	bool getDispalayCrafting() { return displayCrafing; }
	bool setDisplayCrafting(bool newIn) { return displayCrafing = newIn; }
private:
	bool displayCrafing = false;
	int numberOfCraftingItems = 0;
	int craftingIconSize = 25;
	std::vector<std::shared_ptr<Button>> CraftingButtons;
	std::string backgroundTextureLocation = "Resources\\Sprites\\\Toolbar\\";
	Texture backgroundTexture;
	Inventory CraftingInventoryList;
	
};

