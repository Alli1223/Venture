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
			isSEEDS,
			isWHEAT
		} Food;

		enum Tool
		{
			none,
			isAXE,
			isHOE,
			isSCYTHE,
			
		}Tool;
	} ItemType;
	
	ItemType type;
	bool isInInventory = false;
};

