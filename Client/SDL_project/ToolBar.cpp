#include "stdafx.h"
#include "ToolBar.h"


ToolBar::ToolBar()
	: toolBarBackground("Resources\\Toolbar\\toolbarBackground.png"),
	roomCell("Resources\\roomSprites\\center.png"), emptyCell("Resources\\roomSprites\\emptyCell.png"), 
	emptyCellIcon("Resources\\Toolbar\\empty.png"),
	DoorTexture("Resources\\door_sprite.png"),
	HydroponicsIconTexture("Resources\\Toolbar\\hydroponicsIcon2.png"),
	BedIconTexture("Resources\\Toolbar\\Bed.png"),
	ShipDockTexture("Resources\\Toolbar\\SpaceDockIcon.png"),
	ToiletIconTexture("Resources\\Toolbar\\Toilet.png")
{

}


ToolBar::~ToolBar()
{
}

void ToolBar::RenderToolbar(SDL_Renderer* renderer, int& WINDOW_WIDTH, int& WINDOW_HEIGHT, int& mouseX, int& mouseY)
{
	
	if (toolbarRender)
	{
		toolbarSizeX = WINDOW_WIDTH - (WINDOW_WIDTH / 4);
		toolbarSizeY = WINDOW_HEIGHT / 15;
		toolbarXpos = WINDOW_WIDTH / 2;
		toolbarYpos = (WINDOW_HEIGHT - toolbarSizeY);
		int toobarIconXPos = toolbarXpos - (toolbarIconSize * 10);
		if (fillLevelWithCells)
		{

			// Set the icons position and ID
			for (int i = 1; i <= numberOfIcons; i++)
			{
				Icon icon;

				auto sharedIcon = std::make_shared<Icon>(icon);
				sharedIcon->setX(toobarIconXPos);
				sharedIcon->setY(toolbarYpos);
				toobarIconXPos = toobarIconXPos + toolbarIconSize * 2;

				sharedIcon->setIconID(i);

				allIcons.push_back(sharedIcon);
			}
			fillLevelWithCells = false;
		}


		toolBarBackground.alterTransparency(200);
		toolBarBackground.render(renderer, toolbarXpos, toolbarYpos, toolbarSizeX, toolbarSizeY);

		for each (auto icon in allIcons)
		{

			//ICON ONE
			if (icon->getIconID() == 1)
			{
				roomCell.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);


				if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
				{
					roomCell.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						setToolbarSelection(1);
					}
				}
			}
			else if (icon->getIconID() == 2)
			{
				// ICON TWO
				emptyCellIcon.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
				if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
				{
					emptyCellIcon.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						setToolbarSelection(2);
					}
				}
			}
			// ICON THREE
			else if (icon->getIconID() == 3)
			{
				if (numberOfItem3 > 0)
				{
					DoorTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
					if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
					{
						DoorTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
						if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
						{
							setToolbarSelection(3);
						}
					}
				}
			}
			//ICON FOUR
			else if (icon->getIconID() == 4)
			{
				if (numberOfItem4 > 0)
				{
					HydroponicsIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
					if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
					{

						HydroponicsIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
						if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
						{
							setToolbarSelection(4);
						}
					}
				}
			}

			// ICON FIVE (ShipDock)
			else if (icon->getIconID() == 5)
			{
				if (numberOfItem5 > 0)
				{
					ShipDockTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
					if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
					{
						ShipDockTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
						if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
						{
							setToolbarSelection(5);
						}
					}
				}
			}

			// ICON SIX (Bed)
			else if (icon->getIconID() == 6)
			{
				if (numberOfItem6 > 0)
				{
					BedIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
					if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
					{

						BedIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
						if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
						{
							setToolbarSelection(6);
						}
					}
				}
			}
			else if (icon->getIconID() == 7)
			{
				ToiletIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize, toolbarIconSize);
				if (mouseX > icon->getX() - (toolbarIconSize / 2) && mouseX < icon->getX() + (toolbarIconSize / 2) && mouseY > toolbarYpos - toolbarIconSize / 2 && mouseY < toolbarYpos + toolbarSizeY / 2)
				{

					ToiletIconTexture.render(renderer, icon->getX(), icon->getY(), toolbarIconSize + mouseOverSizeIncrease, toolbarIconSize + mouseOverSizeIncrease);
					if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						setToolbarSelection(7);
					}
				}
			}
		}
	}
}

