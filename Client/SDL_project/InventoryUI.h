#pragma once
#include "GUI.h"
#include "Icon.h"
#include "Inventory.h"
class InventoryUI : public GUI
{
public:
	InventoryUI();
	~InventoryUI();
	void RenderInventory(SDL_Renderer* renderer, Inventory& inventory);
	void CreateInventory(SDL_Renderer* renderer, Inventory& inventory);
	int getIconSize() { return iconSize; }
	int setIconSize(int newSize) { return iconSize = newSize; }
	bool getDispalayInventory() { return displayInventory; }
	bool setDisplayInventory(bool newIn) { return displayInventory = newIn; }

	std::vector<std::shared_ptr<Icon>>& getInventoryIcons() { return inventoryIcons; }
private:
	std::vector<std::shared_ptr<Icon>> inventoryIcons;
	Texture backgroundTexture;
	std::string iconTextureLocation = "Resources\\Sprites\\\Toolbar\\";
	bool displayInventory = true;
	int numOfInventoryIcons = 0;
	int iconSize = 25;
};

