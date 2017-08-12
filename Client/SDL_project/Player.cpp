#include "stdafx.h"
#include "Player.h"


Player::Player() : characterTex(characterTextureLocation + "animTemplate.png"), jacket(clothesTextureLocation + "Jacket.png"), jeans(clothesTextureLocation + "Jeans.png"), shortHair(clothesTextureLocation + "Hair.png"), longHair(clothesTextureLocation + "LongHair.png"),
eyes(clothesTextureLocation + "Eyes.png")
{
}


Player::~Player()
{
}

void Player::RenderPlayer(SDL_Renderer* renderer, bool renderCenter)
{
	walkR.maxFrames = 6;
	//walkR.oscillate = true;
	walkR.OnAnimate();

	if (renderCenter)
	{
		renderOffset.x = screenCenter.x;
		renderOffset.y = screenCenter.y;
	}
	else
	{
		renderOffset.x = getX();
		renderOffset.y = getY();
	}
	//characterTex.renderRotation(renderer, renderOffset.x, renderOffset.y, walkR.getCurrentFrame() * 32, getSize(),getSize(), getSize(), getRotation());
	characterTex.renderAnim(renderer, walkR.getCurrentFrame() * 32, 0, screenCenter.x, screenCenter.y, 32, 32, 32);


	switch (PlayerClothes.hair)
	{
	case Clothing::blackHair:
		hairColour = { 10, 10, 10 };
		break;
	case Clothing::brownHair:
		hairColour = { 139,69,19 };
		break;
	case Clothing::redHair:
		hairColour = { 200, 25, 25 };
		break;
	case Clothing::pinkHair:
		hairColour = { 255, 182, 193 };
	}
	shortHair.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
	longHair.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);

	

	//Render head wear texture
	
	switch (PlayerClothes.eyes)
	{
	case Clothing::brownEye:
		eyeColour = { 139,69,19 };
		break;
	case Clothing::greenEye:
		eyeColour = { 34,139,34 };
		break;
	case Clothing::blueEye:
		eyeColour = { 0, 191, 255 };
		break;
	}
	eyes.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
	eyes.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());

	//Render head wear texture
	switch (PlayerClothes.head)
	{
	case Clothing::shortHair:
		shortHair.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
		break;
	case Clothing::longHair:
		longHair.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
		break;
	}

	//Render legs
	switch (PlayerClothes.body)
	{
	case Clothing::jacket:
		jacket.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
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
		jeans.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
		break;

	case Clothing::skirt:

		break;
	}

	
}

//TODO: Calcualte number of values in each enum
void Player::calcualteNumofvalues()
{
	
	for (int i = Clothing::redHair; i != Clothing::gingerHair; i++)
	{

	}
	
}