#pragma once
#include "GUI.h"
#include "TextUI.h"
class Button : public GUI
{
public:
	Button(std::string newText);
	~Button();
	//! Render the button
	void render(SDL_Renderer* renderer, int x, int y, int width, int height);

	// Change the buttons text
	std::string setText(std::string newText) { return text = newText; }


private:
	//! Buttons text
	std::string text;
	//! buttons texture location
	std::string buttonTextureLocation = "Resources\\Sprites\\Menu\\";
	SDL_Color buttonTextColour = { 255, 255, 255 };
	TextUI buttonText;
	Texture buttonBackground;
};

