#include "AnimatedObject.h"



AnimatedObject::AnimatedObject(const char *filename, int frames, int speed, SDL_Rect srcRect, SDL_Rect destRect)
{
	texture = TextureManager::LoadTexture(filename);
	this->srcRect.x = this->srcRect.y = 0;
	this->srcRect.w = srcRect.w;
	this->srcRect.h = srcRect.h;
	this->frames = frames;
	this->speed = speed;
	this->destRect = destRect;
}

AnimatedObject::AnimatedObject(const char *filename, int frames, int speed, SDL_Rect srcRect) {
	texture = TextureManager::LoadTexture(filename);
	this->srcRect.x = this->srcRect.y = 0;
	this->srcRect.w = srcRect.w;
	this->srcRect.h = srcRect.h;
	this->frames = frames;
	this->speed = speed;
}


AnimatedObject::~AnimatedObject()
{
	SDL_DestroyTexture(texture);
}

void AnimatedObject::update() {
	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

void  AnimatedObject::render() {
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}

void AnimatedObject::setPosition(SDL_Rect destRect) {
	this->destRect = destRect;
}
