#pragma once
#include "Point.h"
#include "Texture.h"
#include "Inventory.h"
#include "Items.h"
#include "PathFinder.h"
class Character
{
public:
	Character();
	~Character();


	//Getter methods
	//! Gets the characters X value
	int getX() { return x; }
	//! Gets the characters Y value
	int getY() { return y; }
	//! Gets the characters X offsetvalue
	int getOffsetX() { return offsetX; }
	//! Gets the characters Y offsetvalue
	int getOffsetY() { return offsetY; }
	//! Gets the characters X value
	int getCellX() { return cellX; }
	//! Gets the characters Y value
	int getCellY() { return cellY; }
	//! Gets the characters size
	int getSize() { return size; }
	//! Gets the characters speed
	double getSpeed() { return speed; }
	//! Gets and the agents health
	double getHealth() { return health; }

	//! Agent ID
	std::string getID() { return ID; }
	std::string setID(std::string newID) { return ID = newID; }

	//Setter methods
	//! Sets the characters X value
	int setX(int newX) { return x = newX; }
	//! Sets the characters Y value
	int setY(int newY) { return y = newY; }
	//! Sets the characters cellX offset value
	int setOffsetX(int newOffsetX) { return offsetX = newOffsetX; }
	//! Sets the characters Y offset value
	int setOffsetY(int newOffsetY) { return offsetY = newOffsetY; }
	//! Sets the characters cellX value
	int setCellX(int newCellX) { return cellX = newCellX; }
	//! Sets the characters cellY value
	int setCellY(int newCellY) { return cellY = newCellY; }
	//! Sets the position that takes 2 arguments, x and y
	int setPosition(int newX, int newY) { return x = newX, y = newY; }
	//! Sets the characters current speed
	double setSpeed(double newSpeed) { return speed = newSpeed; }
	//! Sets the characters health
	double setHealth(double newHealth) { return health = newHealth; }

	//! Gets and sets the agents point location
	Point getAgentPointLocation() { return agentPointLocation; }
	Point setAgentPointLocation(Point newPointLocation) { return agentPointLocation = newPointLocation; }

	bool isMoving = false;

private:
	//! string stores agent ID/Name
	std::string ID = "";
	//! Integers for the agent's X and Y position
	int offsetX = 0, offsetY = 0;
	int x = 0; int y = 0;
	//! Integers for the agent's cellX and cellY positions below agent
	int cellX = 0; int cellY = 0;
	//! Point for where the agent is located
	Point agentPointLocation;
	//! Integer for the agent's size when rendered
	int size = 25;
	//! Integer for the agent current speed
	float speed = 2.0;
	//! A double for the agents's health
	double health = 100.0;
};
