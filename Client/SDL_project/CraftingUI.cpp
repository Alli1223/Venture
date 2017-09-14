#include "stdafx.h"
#include "CraftingUI.h"


CraftingUI::CraftingUI() : backgroundTexture(backgroundTextureLocation + "InventoryBackground.png")
{

	// Create the crafting list
	Item item;
	Item item2;
	Item item3;
	Item item4;
	item.type.Resource = Item::ItemType::isSTONEWALL;
	item2.type.Resource = Item::ItemType::isWOOD;
	item3.type.Resource = Item::ItemType::isSTONEWALL;
	item4.type.Resource = Item::ItemType::isWOODFENCE;
	CraftingInventoryList.add(item);
	CraftingInventoryList.add(item2);
	CraftingInventoryList.add(item3);
	CraftingInventoryList.add(item4);
}


CraftingUI::~CraftingUI()
{
}

void CraftingUI::renderCraftingMenu(SDL_Renderer* renderer)
{
	if (displayCrafing)
	{
		backgroundTexture.alterTransparency(150);
		backgroundTexture.alterTextureColour(150, 25, 25);
		backgroundTexture.render(renderer, getX(), getY(), getWidth(), getHeight());

		//Create or update
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
		else
		{// Render Buttons

			for each (auto &button in CraftingButtons)
			{
				button->buttonIcon.renderBackground = false;
				button->setMouseOverIncreaseSize(false);
				button->render(renderer, button->getX(), button->getY(), button->getWidth(), button->getHeight());
			}
		}
	}
}