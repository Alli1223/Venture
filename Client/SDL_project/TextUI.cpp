#include "stdafx.h"
#include "TextUI.h"


TextUI::TextUI(std::string fontType) : FontType(fontType), texture(nullptr)
{
}


TextUI::~TextUI()
{
}

void TextUI::render(SDL_Renderer* renderer, std::string text, int x, int y, int width, int height)
{

}
