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

	enum Resource
	{
		isWOOD,
		isSTONE,
		isBERRY,
		isFISH
	};
	

	bool isInInventory = false;


	std::string itemFileDirectory = "Resources\\SpawnItems\\";
	Texture berryTexture;
};

