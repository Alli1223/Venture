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
			isSTONE
		} Resource;
		enum Food
		{
			isBERRY,
			isFISH,
			isSEEDS
		} Food;

		enum Tool
		{
			none,
			isAXE,
			isHOE
		}Tool;
	} ItemType;
	
	ItemType type;
	bool isInInventory = false;
};

