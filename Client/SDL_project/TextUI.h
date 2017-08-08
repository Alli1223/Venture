#pragma once
class TextUI
{
public:
	//! Font types are "Sans" and "Ostrich"
	TextUI(std::string fontType);
	~TextUI();

	void render(SDL_Renderer* renderer, std::string text, int x, int y, int width, int height, SDL_Color Colour);

	//! Loads the texture
	SDL_Texture* getTexture() { return texture; }
private:
	SDL_Texture* texture;
	//SDL_Texture* Message;
	SDL_Rect Message_rect;
	std::string FontType;
};

