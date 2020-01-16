#include "TextBox.h"



TextBox::TextBox(int x, int y, int width, int height, std::string text)
{
	if (TTF_Init() < 0) {
		std::cout << "Font errors" << std::endl;
	}
	font = TTF_OpenFont("assets/arial.ttf", 20);
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), White);
	message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
}


TextBox::~TextBox()
{
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
	TTF_CloseFont(font);
}

void TextBox::render() {
	SDL_RenderCopy(Game::renderer, message, NULL, &destRect);
}

void TextBox::clean() {
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
	TTF_CloseFont(font);
}

void TextBox::changeText(std::string &text) {
	SDL_FreeSurface(surfaceMessage);
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), White);
	message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);
}