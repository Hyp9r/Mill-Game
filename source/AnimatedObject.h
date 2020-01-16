#pragma once
#include "TextureManager.h"
#include "SDL.h"
class AnimatedObject
{
public:
	AnimatedObject(const char* filename, int frames, int speed, SDL_Rect srcRect, SDL_Rect destRect);
	AnimatedObject(const char* filename, int frames, int speed, SDL_Rect srcRect);
	~AnimatedObject();
	void render();
	void update();
	void setPosition(SDL_Rect destRect);
private:
	SDL_Texture *texture;
	int frames;
	int speed;
	SDL_Rect srcRect, destRect;
};

