#include "stdafx.h"
#include "ToolBar.h"


ToolBar::ToolBar()
	
{

}


ToolBar::~ToolBar()
{
}

void ToolBar::RenderToolbar(SDL_Renderer* renderer, GameSettings& gameSettings)
{
	
	int mouseX, mouseY;
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
	
	}
	if (toolbarRender)
	{
		
		// Set the icons position and ID
		for each (auto &icon in allIcons)
		{
			icon->RenderIcon(renderer);
			
		}
	}
}

void ToolBar::createToolbar(Player& player, GameSettings& gameSettings)
{
	int WW = gameSettings.WINDOW_WIDTH;
	int WH = gameSettings.WINDOW_HEIGHT;
	std::vector<Item> playeritems;
	for (int i = 0; i < player.inventory.getSize(); i++)
	{
		playeritems.push_back(player.inventory.get(i));
	}
	
	for (int i = 1; i <= numberOfIcons; i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);
		int startX = WW / 2 - (WW / 4);
		int iconSize = WW / 25;
		if(player.inventory.getSize() > 1)
			sharedIcon->setIconItem(playeritems.at(1));
		sharedIcon->setX(startX + (i * iconSize));
		sharedIcon->setY(WH - iconSize);
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		allIcons.push_back(sharedIcon);
	}
}

