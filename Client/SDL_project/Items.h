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
	int getItemHealth() { return itemHealth; }
	int setItemHealth(int newHealth) { return itemHealth = newHealth; }
	typedef struct
	{
		enum Resource
		{
			noResource,
			isWOOD,
			isSTONE
		} Resource;
		enum Food
		{
			noFood,
			isBERRY,
			isFISH,
			isSEEDS,
			isWHEAT
		} Food;

		enum Tool
		{
			noTool,
			isWOODAXE,
			isPICKAXE,
			isHOE,
			isSCYTHE,
			isWATERINGCAN,
			isFISHINGROD
			
		}Tool;
	} ItemType;
	
	ItemType type;
	bool isInInventory = false;
private:
	int itemHealth = 100;
};

