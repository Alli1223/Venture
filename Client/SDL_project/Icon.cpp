#include "stdafx.h"
#include "Icon.h"


Icon::Icon() : AxeTexture(iconTextureLocation + "axe.png"), hoeTexture(iconTextureLocation + "hoe.png"), seedsTexture(iconTextureLocation + "seeds.png"), ScytheTexture(iconTextureLocation + "scythe.png"), WheatTexture(iconTextureLocation + "wheat.png"),
FishingRodTexture(iconTextureLocation + "fishingPole.png"), WateringCanTexture(iconTextureLocation + "wateringCan.png"), WoodTexture(iconTextureLocation + "wood.png")
{
}


Icon::~Icon()
{
}

void Icon::RenderIcon(SDL_Renderer* renderer)
{
	switch (iconItem.type.Tool)
	{
	case Item::ItemType::isAXE:
		AxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isHOE:
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isSCYTHE:
		ScytheTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isFISHINGROD:
		FishingRodTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isWATERINGCAN:
		WateringCanTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	}
	switch (iconItem.type.Food)
	{
	case Item::ItemType::isSEEDS:
		seedsTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isWHEAT:
		WheatTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	}
	switch (iconItem.type.Resource)
	{
	case Item::ItemType::isWOOD:
		WoodTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	}

	/*
	if(this->iconItem.type.isAxe)
		AxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
	else if (this->iconItem.type.isHoe)
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		*/
}