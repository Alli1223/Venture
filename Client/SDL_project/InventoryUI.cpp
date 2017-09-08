#include "stdafx.h"
#include "InventoryUI.h"


InventoryUI::InventoryUI() : backgroundTexture(iconTextureLocation + "InventoryBackground.png")
{
}


InventoryUI::~InventoryUI()
{
}

void InventoryUI::RenderInventory(SDL_Renderer* renderer, GameSettings& gameSettings, Player& player)
{
	for (int i = 0; i < player.inventory.getSize(); i++)
	{
		inventoryIcons[i]->setIconItem(player.inventory.get(i));
	}
	for each (auto &icon in inventoryIcons)
	{
		icon->RenderIcon(renderer);
	}
	
}
void InventoryUI::CreateInventory(SDL_Renderer* renderer, GameSettings& gameSettings, Player& player)
{
	int WW = gameSettings.WINDOW_WIDTH;
	int WH = gameSettings.WINDOW_HEIGHT;

	for (int i = 0; i < player.inventory.getSize(); i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);
		
		int iconSize = WW / 25;

		sharedIcon->setX(getX() + (i * iconSize));
		sharedIcon->setY(getY());
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		inventoryIcons.push_back(sharedIcon);
	}
}