#include "stdafx.h"
#include "Player.h"


Player::Player() : characterTex(characterTextureLocation + "animTemplate.png"), jacket(clothesTextureLocation + "Jacket.png"), jeans(clothesTextureLocation + "Jeans.png"), shortHair(clothesTextureLocation + "Hair.png"), longHair(clothesTextureLocation + "LongHair.png"),
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
	blink.setFrameRate(200);
	blink.oscillate = true;

	//blink.addDelay(3000, 500);
	//blink.OnAnimate();
	
	
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

	
	// Alter colours

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

	/// RENDER ROTATIONS ///
	//Walk Down
	if (getTargetRotation() == 0 || getTargetRotation() == 360)
	{
		characterTex.renderAnim(renderer, walk.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, getSize());
	}
	// Walk Left
	else if (getTargetRotation() == 90)
	{
		sideWalk.renderAnim(renderer, walk.getCurrentFrame() * 32, 32, renderOffset.x, renderOffset.y, 32, 32, getSize());
		sideBlink.renderAnim(renderer, blink.getCurrentFrame() * 32, 32, renderOffset.x, renderOffset.y, 32, 32, getSize());
	}
	// Walk Right
	else if (getTargetRotation() == 270)
	{
		sideWalk.renderAnim(renderer, walk.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, getSize());
		sideBlink.renderAnim(renderer, blink.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, getSize());
	}
	else if (getTargetRotation() == 180)
	{
		characterTex.renderAnim(renderer, walk.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, getSize());
	}
	if (getTargetRotation() == 180 || getTargetRotation() == 0)
		eyes.renderAnim(renderer, blink.getCurrentFrame() * 32, 0, renderOffset.x, renderOffset.y, 32, 32, 0);
	


	//Render head wear texture
	switch (PlayerClothes.head)
	{
	case Clothing::shortHair:
		//shortHair.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
		break;
	case Clothing::longHair:
		//longHair.renderRotation(renderer, renderOffset.x, renderOffset.y, getSize(), getSize(), getRotation());
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