#pragma once
#include "GUI.h"
#include "Texture.h"
class Icon : public GUI
{
public:
	//! Constructor
	Icon();
	//! Destructor
	~Icon();

	int getIconID() { return iconID; }
	int setIconID(int newIconID) { return iconID = newIconID; }
	void RenderIcon(SDL_Renderer* renderer);


	Item& getIconItem() { return iconItem; }
	Item setIconItem(Item newIcon) { return iconItem = newIcon; }
	
private:
	Item iconItem;
	std::string iconTextureLocation = "Resources\\Sprites\\\Toolbar\\";

	//Refactor this to be more memory effecient
	Texture AxeTexture;
	Texture hoeTexture;
	Texture seedsTexture;
	Texture WheatTexture;
	Texture ScytheTexture;
	Texture FishingRodTexture;
	Texture WateringCanTexture;

	int iconID;
};

