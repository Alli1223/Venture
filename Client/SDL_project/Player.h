#pragma once
#include "Character.h"
#include "Animation.h"
class Player : public Character
{
public:
	Player();
	~Player();
	
	void RenderPlayer(SDL_Renderer* renderer, bool useOffset);
	void renderCharacterItems(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize);
	
	glm::vec2 renderOffset;
	glm::vec2 screenCenter;
	int xOffset, yOffset;
	Clothing PlayerClothes;

	Animation getWalkAnimation() { return walkAnimation; }

private:
	// Unused function that may be useful later
	void calcualteNumofvalues();
	//! Pixel size of the player sprite in the spritesheet
	int pixelSize = 32;
	//! Default colours
	SDL_Color hairColour = { 255,255,255 };
	SDL_Color eyeColour = { 255,255,255 };
	//! Texture locations
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Sprites\\Character\\Clothes\\";

	//! Texture for the Character
	Texture characterTexture;
	Texture walkTexture;
	Texture sideBlinkTexture;
	Texture shortHairTexture;
	Texture longHairTexture;
	Texture eyesTexture;
	
	//! Texture for the clothes
	Texture jacketTexture;
	Texture jeansTexture;
	
	//! Animations
	Animation walkAnimation;
	Animation blinkAnimation;

	

};

