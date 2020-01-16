#pragma once
#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include "Player.h"
#include "TextBox.h"
#include "AudioPlayer.h"

class Game 
{
public:
	Game();
	~Game();

	enum GameState{ START_STATE, MENU_STATE, PLAY_STATE, GAMEOVER_STATE};
	
	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	void isOver();
	void restartPlayerTurn();
	
	bool running() {
		return isRunning;
	}
	void setPlayerTurn();
	

	static SDL_Renderer *renderer;



private:
	void handleSlides();
	void didPlayersPlaceAllPiecesOnField();
	void handleEating(int piece);
	bool eatPiece(int piece);
	bool isRunning;
	SDL_Window *window;
	GameState currentState = START_STATE;
	int selectedPiece = -1; //this variable is used to store selected piece so we can later used it to move the piece
	AudioPlayer *audio,*audio2;
};

