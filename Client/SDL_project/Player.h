#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();



private:
	int x = 0, y = 0;
	std::string characterTextureLocation = "Resources\\Character\\";
	//! For the Character
	Texture characterTex;
};

