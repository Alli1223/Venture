#include "stdafx.h"
#include "Player.h"


Player::Player() : characterTex(characterTextureLocation + "Alli.png"), jacket(clothesTextureLocation + "Jacket.png"), jeans(clothesTextureLocation + "Jeans.png"), hairShape(clothesTextureLocation + "Hair.png")
{
}


Player::~Player()
{
}

void Player::RenderPlayer(SDL_Renderer* renderer)
{
	characterTex.renderRotation(renderer, getX(), getY(), getSize(), getSize(), getRotation());

	switch (PlayerClothes.hair)
	{
	case Clothing::black:
		hairColour = { 10, 10, 10 };
		break;
	case Clothing::red:
		hairColour = { 200, 25, 25 };
		break;
	case Clothing::pink:
		hairColour = { 255, 182, 193 };
	}
	hairShape.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
	hairShape.renderRotation(renderer, getX(), getY(), getSize(), getSize(), getRotation());

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
	case Clothing::jacket:
		jacket.renderRotation(renderer, getX(), getY(), getSize(), getSize(), getRotation());
		break;
	case Clothing::dress:

		break;

	case Clothing::tshirt:

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