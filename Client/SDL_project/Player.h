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
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Sprites\\Character\\Clothes\\";
	//! For the Character
	Texture characterTex;

	Texture jacket;
	Texture jeans;
};

