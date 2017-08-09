#include "stdafx.h"
#include "Player.h"


Player::Player() : characterTex(characterTextureLocation + "Alli.png"), jacket(clothesTextureLocation + "Jacket.png"), jeans(clothesTextureLocation + "Jeans.png")
{
}


Player::~Player()
{
}

void Player::RenderPlayer(SDL_Renderer* renderer)
{
	characterTex.renderRotation(renderer, getX(), getY(), getSize(), getSize(), getRotation());
	//Render head wear texture
	switch (PlayerClothes.head)
	{
	case Clothing::noHeadWear:
		//Donothing
		break;
	case Clothing::hat:
		break;
	}
	//Render legs
	switch (PlayerClothes.body)
	{
	case Clothing::dress:

		break;

	case Clothing::tshirt:

		break;

	case Clothing::jacket:
		jacket.renderRotation(renderer, getX(), getY(), getSize(), getSize(), getRotation());
		break;
	}
	//Render leg wear
	switch (PlayerClothes.leg)
	{
	case Clothing::chinos:

		break;

	case Clothing::jeans:
		jeans.renderRotation(renderer, getX(), getY(), getSize(), getSize(), getRotation());
		break;

	case Clothing::skirt:

		break;
	}
}