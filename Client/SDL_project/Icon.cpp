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
	if(iconItem.type.isAxe)
		AxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
	else if (iconItem.type.isHoe)
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
}