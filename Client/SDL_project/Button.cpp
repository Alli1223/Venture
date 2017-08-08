#include "stdafx.h"
#include "Button.h"


Button::Button(std::string newText) : buttonText("Sans"), text(newText), buttonBackground(buttonTextureLocation + "Button.png")
{
}

Button::~Button()
{
}

void Button::render(SDL_Renderer* renderer, int x, int y, int width, int height)
{
	// Set object variables
	setX(x), setY(y), setWidth(width), setHeight(height);
	//Render background
	buttonBackground.render(renderer, getX(), getY(), getWidth(), getHeight());
	// If the button has text, render it in the center of the button
	if (text.size() > 0)
		buttonText.render(renderer, text, getX() - (getWidth() / 2), getY() - (getHeight() / 2), getWidth(), getHeight(), buttonTextColour);
}

