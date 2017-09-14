#include "stdafx.h"
#include "CraftingUI.h"


CraftingUI::CraftingUI() : backgroundTexture(backgroundTextureLocation + "InventoryBackground.png")
{

	// Create the crafting list
	Item item;
	Item item2;
	item.type.Resource = Item::ItemType::isSTONEWALL;
	item2.type.Resource = Item::ItemType::isWOOD;
	CraftingInventoryList.add(item);
	CraftingInventoryList.add(item2);
}


CraftingUI::~CraftingUI()
{
}

void CraftingUI::renderCraftingMenu(SDL_Renderer* renderer)
{
	backgroundTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
	
	//Create
	if (numberOfCraftingItems != CraftingInventoryList.getCurrentSize())
	{
		int x = getX() - getWidth() / 2 + craftingIconSize;
		int y = getY() - getHeight() / 2 + craftingIconSize * 2;
		for (int i = 0; i < CraftingInventoryList.getCurrentSize(); i++)
		{
			if (x > getX() + getWidth() / 2 - craftingIconSize)
			{
				x = getX() - getWidth() / 2 + craftingIconSize;
				y += craftingIconSize;
			}
			
			Button button("");
			auto sharedButton = std::make_shared<Button>(button);
			sharedButton->buttonIcon.setIconItem(CraftingInventoryList.get(i));
			sharedButton->setX(x);
			sharedButton->setY(y);
			sharedButton->setWidth(craftingIconSize);
			sharedButton->setHeight(craftingIconSize);
			CraftingButtons.push_back(sharedButton);
			x += craftingIconSize;
		}
		numberOfCraftingItems = CraftingInventoryList.getCurrentSize();
	}
	//Update
	else
	{
		for each (auto &button in CraftingButtons)
		{
			button->render(renderer, button->getX(), button->getY(), button->getWidth(), button->getHeight());
		}
	}
	

	// Render Buttons

}