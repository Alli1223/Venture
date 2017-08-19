#include "stdafx.h"
#include "Icon.h"


Icon::Icon() : AxeTexture(iconTextureLocation + "axe.png"), hoeTexture(iconTextureLocation + "hoe.png")
{
}


Icon::~Icon()
{
}

void Icon::RenderIcon(SDL_Renderer* renderer)
{
	switch (iconItem.type.Tool)
	{
	case Item::ItemType::isAxe:
		AxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isHoe:
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	}
	/*
	if(this->iconItem.type.isAxe)
		AxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
	else if (this->iconItem.type.isHoe)
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		*/
}