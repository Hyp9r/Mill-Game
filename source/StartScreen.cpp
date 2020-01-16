#include "StartScreen.h"
#include "AnimatedObject.h"

AnimatedObject * animatedObject;

StartScreen::StartScreen()
{
	animatedObject = new AnimatedObject("assets/helper.png", 3, 300, srcRect, destRect);
	info1 = new TextBox(200, 500, 450, 30, "This object shows available positions where you can place pieces");
	info2 = new TextBox(200, 500, 450, 30, "This object shows how player 1 piece looks like");
	info3 = new TextBox(200, 500, 450, 30, "This object shows how player 2 piece looks like");
}


StartScreen::~StartScreen()
{
}

void StartScreen::render() {
	switch (slide)
	{
	case 0:
		//SDL_RenderCopy(Game::renderer, helperCircle, &srcRect, &destRect);
		animatedObject->render();
		info1->render();
		break;
	case 1:
		SDL_RenderCopy(Game::renderer, redPiece, &srcRect1, &destRect1);
		info2->render();
		break;
	case 2:
		SDL_RenderCopy(Game::renderer, greenPiece, &srcRect2, &destRect2);
		info3->render();
		break;
	case 3:
		break;
	}
	
}

void StartScreen::update() {
	animatedObject->update();
}

void StartScreen::setCurrentSlide(int slide) {
	this->slide = slide;
}

int StartScreen::getCurrentSlide() {
	return this->slide;
}

void StartScreen::clean() {
	delete animatedObject;
	delete info1,info2,info3;
	SDL_DestroyTexture(helperCircle);
	SDL_DestroyTexture(redPiece);
	SDL_DestroyTexture(greenPiece);
}

