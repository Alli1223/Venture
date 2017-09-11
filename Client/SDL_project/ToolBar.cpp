#include "stdafx.h"
#include "ToolBar.h"


ToolBar::ToolBar() : selectionTexture("Resources\\Sprites\\Toolbar\\grey.png")
{
	selectionTexture.alterTransparency(150);
}


ToolBar::~ToolBar()
{
}
Item& ToolBar::getSelectedItem()
{
	auto& item = toolbarIcons.at(toolbarSelection);
	return item->getIconItem();
}

void ToolBar::RenderToolbar(SDL_Renderer* renderer, GameSettings& gameSettings)
{
	selectionTexture.alterTransparency(150);
	int mouseX, mouseY;
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
	
	}
	if (toolbarRender)
	{
		// Set the icons position and ID
		for each (auto &icon in toolbarIcons)
		{
			icon->RenderIcon(renderer);
		}
	}
	for(int i = 0; i < numberOfIcons; i++ )
	{
		if (i == toolbarSelection)
			selectionTexture.render(renderer, toolbarIcons[i]->getX(), toolbarIcons[i]->getY(), toolbarIcons[i]->getWidth(), toolbarIcons[i]->getHeight());
		
	}
}

void ToolBar::Update(Player& player, GameSettings& gameSettings)
{
	for (int i = 0; i < player.inventory.getCurrentSize(); i++)
	{
		if (i < numberOfIcons)
			toolbarIcons[i]->setIconItem(player.inventory.get(i));
	
	}
	// Loop the toolbar when the player gets to the end
	if (toolbarSelection > numberOfIcons)
		toolbarSelection = 0;
	if (toolbarSelection < 0)
		toolbarSelection = numberOfIcons;
	
}
void ToolBar::createToolbar(Player& player, GameSettings& gameSettings)
{
	int WW = gameSettings.WINDOW_WIDTH;
	int WH = gameSettings.WINDOW_HEIGHT;
	
	for (int i = 1; i <= numberOfIcons; i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);
		int startX = WW / 2 - (WW / 4);
		int iconSize = WW / 25;
			
		sharedIcon->setX(startX + (i * iconSize));
		sharedIcon->setY(WH - iconSize);
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		toolbarIcons.push_back(sharedIcon);
	}
}

