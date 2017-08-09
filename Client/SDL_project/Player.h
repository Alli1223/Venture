#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	~Player();
	
	void RenderPlayer(SDL_Renderer* renderer);

	typedef struct
	{
		enum HairColour {
			red,
			yellow,
			pink,
			brown,
			black,
			ginger
		}hair;
		enum HeadWear {
			noHeadWear,
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
	
	bool gender = false;
	Clothing PlayerClothes;
private:
	SDL_Color hairColour = { 255,255,255 };
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Sprites\\Character\\Clothes\\";
	//! For the Character
	Texture characterTex;
	Texture hairShape;

	Texture jacket;
	Texture jeans;
};

