#pragma once
#include "SDL.h"
#include "TextureManager.h"
#include "SDL_ttf.h"
class TextBox
{
public:
	TextBox(int x, int y, int width, int height, std::string text);
	~TextBox();
	void render();
	void changeText(std::string &text);
	void clean();
private:
	TTF_Font *font;
	SDL_Rect destRect;
	SDL_Color White = { 255,255,255 };
	SDL_Surface *surfaceMessage;
	SDL_Texture * message;
};

