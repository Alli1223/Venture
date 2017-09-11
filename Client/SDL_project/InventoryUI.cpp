#include "stdafx.h"
#include "InventoryUI.h"


InventoryUI::InventoryUI() : backgroundTexture("Resources\\Sprites\\Toolbar\\InventoryBackground.png")
{
}


InventoryUI::~InventoryUI()
{
}

void InventoryUI::RenderInventory(SDL_Renderer* renderer, Inventory& inventory)
{
	if (displayInventory)
	{
		backgroundTexture.alterTransparency(150);
		backgroundTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		for (int i = 0; i < inventory.getCurrentSize(); i++)
			inventoryIcons[i]->setIconItem(inventory.get(i));
		
		for each (auto &icon in inventoryIcons)
			icon->RenderIcon(renderer);
		
	}
	
}
void InventoryUI::CreateInventory(SDL_Renderer* renderer, Inventory& inventory)
{
	int x = getX() - getWidth() / 2 + iconSize;
	int y = getY() - getHeight() / 2 + iconSize * 2;
	for (int i = 0; i < inventory.getCapacity(); i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);

		if (x > getX() + getWidth() / 2 - iconSize)
		{
			x = getX() - getWidth() / 2 + iconSize;
			y += iconSize;
		}
		sharedIcon->setX(x);
		sharedIcon->setY(y);
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		sharedIcon->renderBackground = true;
		inventoryIcons.push_back(sharedIcon);
		x += iconSize;
	}
		
}