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
	typedef struct
	{
		enum Resource
		{
			isWOOD,
			isSTONE,
		} Resource;
		enum Food
		{
			isBERRY,
			isFISH
		} Food;

		enum Tool
		{
			isAxe,
			isHoe
		}Tool;
	} ItemType;
	
	ItemType type;
	bool isInInventory = false;


	std::string itemFileDirectory = "Resources\\SpawnItems\\";
	Texture berryTexture;
};

