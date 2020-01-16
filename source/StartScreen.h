#pragma once
#include "SDL.h"
#include "TextBox.h"
#include "TextureManager.h"
class StartScreen
{
public:
	StartScreen();
	~StartScreen();
	void render();
	void update();
	void clean();
	int getCurrentSlide();
	void setCurrentSlide(int slide);

private:
	SDL_Texture *helperCircle = TextureManager::LoadTexture("assets/helper.png");
	SDL_Texture *redPiece = TextureManager::LoadTexture("assets/player.png");
	SDL_Texture *greenPiece = TextureManager::LoadTexture("assets/green.png");
	SDL_Rect srcRect = { 0, 0, 60, 60 };
	SDL_Rect destRect = { 400 - 30, 300 - 30, 60,60 };
	SDL_Rect srcRect1 = { 0, 0, 40, 40 };
	SDL_Rect destRect1 = { 400 - 30, 300 - 30, 40,40 };
	SDL_Rect srcRect2 = { 0, 0, 40, 40 };
	SDL_Rect destRect2 = { 400 - 30, 300 - 30, 40,40 };
	int slide = 0;
	TextBox *info1, *info2, *info3;
};

