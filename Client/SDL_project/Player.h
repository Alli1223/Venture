#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();
	
	void RenderPlayer(SDL_Renderer* renderer, bool useOffset);
	
	typedef struct
	{
		enum HairColour {
			redHair,
			yellowHair,
			pinkHair,
			brownHair,
			blackHair,
			gingerHair
		}hair;
		enum EyeColour {
			brownEye,
			greenEye,
			blueEye
		}eyes;

		enum HeadWear {
			noHeadWear,
			shortHair,
			longHair,
			hat
		}head;

		enum ShirtWear {
			noShirt,
			tshirt,
			jacket,
			dress
		}body;
		enum LegWear {
			noLeg,
			jeans,
			chinos,
			skirt
		}leg;
	} Clothing;
	
	glm::vec2 renderOffset;
	glm::vec2 screenCenter;
	int xOffset, yOffset;
	Clothing PlayerClothes;

private:

	
	void calcualteNumofvalues();
	SDL_Color hairColour = { 255,255,255 };
	SDL_Color eyeColour = { 255,255,255 };
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Sprites\\Character\\Clothes\\";
	//! For the Character
	Texture characterTex;
	Texture shortHair;
	Texture longHair;
	Texture eyes;

	Texture jacket;
	Texture jeans;
};

