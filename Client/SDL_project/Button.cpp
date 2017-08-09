#include "stdafx.h"
#include "Button.h"


Button::Button(std::string newText) : buttonText("Ostrich"), text(newText), buttonBackground(buttonTextureLocation + "Red.png")
{
}

Button::~Button()
{
}

void Button::render(SDL_Renderer* renderer, int x, int y, int width, int height)
{
	// Set object variables
	SDL_GetMouseState(&tx, &ty);
	setX(x), setY(y), setWidth(width), setHeight(height);
	if (tx > getX() - (getWidth() / 2) && tx < getX() + (getWidth() / 2) && ty > getY() - (getHeight() / 2) && ty < getY() + (getHeight() / 2))
	{
		setWidth(getWidth() + mouseOverSizeInrease), setHeight(getHeight() + mouseOverSizeInrease);
		
		// Activate the button if it has been pressed
		if (SDL_GetMouseState(&tx, &ty) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			isActivated = true;
		}
		else
		{
			isActivated = false;
		}
		
	}
		
	
	//Render background
	buttonBackground.render(renderer, getX(), getY(), getWidth(), getHeight());

	// If the button has text, render it in the center of the button
	if (text.size() > 0)
		buttonText.render(renderer, text, getX() - (getWidth() / 2), getY() - (getHeight() / 2), getWidth(), getHeight(), buttonTextColour);
}

