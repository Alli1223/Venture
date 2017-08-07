#include "stdafx.h"
#include "TextUI.h"
#include "InitialisationError.h"

TextUI::TextUI(std::string fontType) : FontType(fontType), texture(nullptr)
{
}


TextUI::~TextUI()
{
}

void TextUI::render(SDL_Renderer* renderer, std::string text, int x, int y, int width, int height, SDL_Color Colour)
{
	TTF_Font* font = TTF_OpenFont("Resources\\Fonts\\OpenSans.ttf", height);
	if (FontType == "Ostrich")
	{
		TTF_Font* font = TTF_OpenFont("Resources\\Fonts\\ostrich.ttf", height);
	}
	else if (FontType == "Sans")
	{
		TTF_Font* font = TTF_OpenFont("Resources\\Fonts\\OpenSans.ttf", height);
	}
	else
	{
		throw InitialisationError("FontType is not correct, use \"Sans\" as default.");
	}
	// Create texture from surface
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), Colour);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);


	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = width; // controls the width of the rect
	Message_rect.h = height; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}
