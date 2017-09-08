#pragma once
#include "GUI.h"
#include "Level.h"
#include "Icon.h"
#include "GameSettings.h"
#include "Texture.h"


class ToolBar : public GUI
{
public:
	ToolBar();
	~ToolBar();

	Item& getSelectedItem();
	
	//! Function that renders the toolbar
	void ToolBar::RenderToolbar(SDL_Renderer* renderer, GameSettings& gameSettings);

	std::vector<std::shared_ptr<Icon>> toolbarIcons;


	void createToolbar(Player& player, GameSettings& gameSettings);
	void Update(Player& player, GameSettings& gameSettings);

	int getToolbarSelection() { return toolbarSelection; }
	int setToolbarSelection(int newSelection) { return toolbarSelection = newSelection; }


private:
	Texture selectionTexture;
	std::string toolbarTextureLocation = "Resources\\Sprites\\Toolbar\\";
	int toolbarSelection = 0;
	int numberOfIcons = 10;
	bool toolbarRender = true;
	

};

