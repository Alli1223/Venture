#pragma once
#include "Texture.h"
#include "Level.h"

class Item
{
public:
	//! Constructor
	Item();
	//! Destructor
	~Item();

	struct Item_Type
	{
		enum food
		{
			BERRY,
			FISH
		};
	};

	bool isInInventory = false;


	std::string itemFileDirectory = "Resources\\SpawnItems\\";
	Texture berryTexture;
};

