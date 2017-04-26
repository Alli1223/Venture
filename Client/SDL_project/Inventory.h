#pragma once
#include "Items.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	// Add item to inventory
	bool add(const Item& item)
	{
		if (capacity > items.size())
		{
			items.push_back(item);
			//item.onInsertionFailed() /* A trick I've done in the past to give custom behavior */
			return true;
		}
		return false;
	}

	bool removeItem(const Item& item)
	{
		for (int i = 0; i < capacity; i++)
		{
			//if(items[i].)
		}
	}
	// returns the size of inventory
	unsigned int getCapacity(void) const
	{
		return capacity;
	}
	//Get size of the current inventory
	unsigned int getSize(void) const
	{
		return items.size();
	}

	// May throw
	const Item& get(unsigned int index) const
	{
		return items.at(index);
	}

	// Returns true if the index was removed, false if the index was out of bounds
	bool remove(unsigned int index)
	{
		if (index < items.size())
		{
			items.erase(items.begin() + index);
			return true;
		}
		return false;
	}

private:
	unsigned int capacity = 20;
	std::vector<Item> items;
};

