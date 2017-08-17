#pragma once
#include "GUI.h"
#include "Level.h"
#include "Icon.h"
#include "GameSettings.h"


class ToolBar : public GUI
{
public:
	ToolBar();
	~ToolBar();

	
	
	//! Function that renders the toolbar
	void ToolBar::RenderToolbar(SDL_Renderer* renderer, GameSettings& gameSettings);

	std::vector<std::shared_ptr<Icon>> allIcons;

	void createToolbar(Player& player, GameSettings& gameSettings);
	void Update(Player& player, GameSettings& gameSettings);


private:
	int toolbarSelection = 1;
	int numberOfIcons = 5;
	bool toolbarRender = true;
	

};

