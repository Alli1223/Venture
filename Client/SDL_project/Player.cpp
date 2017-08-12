#include "stdafx.h"
#include "Player.h"


Player::Player() : characterTex(characterTextureLocation + "base.png"), jacket(clothesTextureLocation + "Jacket.png"), jeans(clothesTextureLocation + "Jeans.png"), shortHair(clothesTextureLocation + "Hair.png"), longHair(clothesTextureLocation + "LongHair.png"),
eyes(characterTextureLocation + "eyesAnim.png"), sideWalk(characterTextureLocation + "walkSide.png"), sideBlink(characterTextureLocation + "sideBlink.png")
{
}


Player::~Player()
{
}

void Player::RenderPlayer(SDL_Renderer* renderer, bool renderCenter)
{
	walk.maxFrames = 4;
	blink.maxFrames = 4;
	//blink.setFrameRate(60);
	blink.OnAnimate();



	if(isPlayerMoving())
		walk.OnAnimate();


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
	//characterTex.renderRotation(renderer, renderOffset.x, renderOffset.y, walk.getCurrentFrame() * 32, getSize(),getSize(), getSize(), getRotation());
	
	//Walk Down
	if (getTargetRotation() == 0 || getTargetRotation() == 360)
	{

	}
	// Walk Left
	else if (getTargetRotation() == 90)
	{
		sideWalk.renderAnim(renderer, walk.getCurrentFrame() * 32, 32, renderOffset.x, renderOffset.y, 32, 32, 32);
		sideBlink.renderAnim(renderer, blink.getCurrentFrame() * 32, 32, renderOffset.x, renderOffset.y, 32, 32, 32);
	}
	// Walk Right
	else if (getTargetRotation() == 270)
	{
		sideWalk.renderAnim(renderer, walk.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, 32);
		sideBlink.renderAnim(renderer, blink.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, 32);
	}
	characterTex.renderAnim(renderer, walk.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, 32);

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
	sideBlink.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
	//characterTex.renderAnim(renderer, walk.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, 32);
	//eyes.renderAnim(renderer, blink.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, 32);
	


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
		//jacket.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
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
		//jeans.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
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