#include "Game.h"
#include "TextureManager.h"
#include "StartScreen.h"
#include <string>
#include "Map.h"

SDL_Renderer* Game::renderer = nullptr;
Map *map;
StartScreen *startScreen;
Player *player1, *player2;
TextBox *textBox1;
TextBox *textBox2;
TextBox *textBox3;
Map::PieceType currentPlayerColor;
std::string turnText1 = "Player 1 turn";
std::string turnText2 = "Player 2 turn";
std::string takePieceText1 = "Player 1 can eat one piece";
std::string takePieceText2 = "Player 2 can eat one piece";
std::string movePieceText1 = "Player 1 can move one piece";
std::string movePieceText2 = "Player 2 can move one piece";
std::string gameover1 = "Player 1 has won the game press r to restart";
std::string gameover2 = "Player 2 has won the game press r to restart";
bool eating = false;
bool moving = false;

Game::Game()
{
	
}


Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Everything initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (window) {
			std::cout << "Window created..." << std::endl;
		}

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	

	map = new Map();
	startScreen = new StartScreen();
	player1 = new Player("Red");
	player2 = new Player("Green");
	currentPlayerColor = Map::RED_PIECE;
	textBox1 = new TextBox(10,10,300,20, "Player 1 pieces: 9");
	textBox2 = new TextBox(500, 10, 300, 20, "Player 2 pieces: 9");
	textBox3 = new TextBox(250, 40, 300, 20, "Player 1 turn");

	/*loading sound*/
	audio = new AudioPlayer();
	audio2 = new AudioPlayer();
	audio->load("assets/sound/battle020.wav");
	audio2->load("assets/sound/scifi002.wav");
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_r) {
			map->removeAllPieces();
			map->startAnimatedObjects();
			player1->reset();
			player2->reset();
			moving = false;
			eating = false;
			currentState = PLAY_STATE;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (currentState == PLAY_STATE) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				std::cout << "Mouse X: " << event.button.x << "Mouse Y: " << event.button.y << std::endl;
				int xMousePosition = event.button.x;
				int yMousePosition = event.button.y;
				SDL_Rect *positionsToCollide = map->getPositionRects();
				for (int i = 0; i < 24; i++) {
					if (xMousePosition >= positionsToCollide[i].x && xMousePosition <= positionsToCollide[i].x + positionsToCollide[i].w) {
						if (yMousePosition >= positionsToCollide[i].y && yMousePosition <= positionsToCollide[i].y + positionsToCollide[i].h) {
							std::cout << "Position: " << map->getPosition(positionsToCollide[i]) << std::endl;
							if (selectedPiece != -1) {
								//this means that we have selected a piece and here's where we can move it to other position
								std::list<int> listOfPositions = map->getPosiblePositions(selectedPiece);
								for (std::list<int>::iterator it = listOfPositions.begin(); it != listOfPositions.end(); it++) {
									if (i == *it) {
										if (map->isPositionEmpty(*it)) {
											map->placePiece(*it, currentPlayerColor);
											map->removePiece(selectedPiece);
											selectedPiece = -1;
											map->resetAnimatingAvaliablePositions();
											if (map->hasMill(*it, currentPlayerColor)) {
												/*After moving if the player formed mill set eating to true else set the turn*/
												audio->play();
												if (currentPlayerColor == Map::GREEN_PIECE)
													textBox3->changeText(takePieceText2);
												else
													textBox3->changeText(takePieceText1);
												eating = true;
												std::cout << "Player " << currentPlayerColor << " can eat one piece from other player" << std::endl;
											}
											if(!eating)
												setPlayerTurn();
											break;
										}
									}
								}
							}
							if (moving && !eating) {
								/*If both players placed their pieces on the field and none is currently eating*/
								//then each player can move their pieces
								if (!map->isPositionEmpty(i) && currentPlayerColor == map->checkColor(i)) {
									//get the posible position this piece can move
									//and play animation so the player knows where he can move
									//his piece
									map->resetAnimatingAvaliablePositions();
									std::list<int> listOfPositions = map->getPosiblePositions(i);
									map->animateAvaliablePositions(listOfPositions);
									selectedPiece = i;
								}
							}
							else if (eating) {
								/*if eating is true, that means the one of the players has made mill and can eat one piece from other player*/
								handleEating(i);
								break;
							}
							else {
								/*This part is responsible for placing pieces when players still have pieces left and noone is eating a piece currently*/
								if (map->placePiece(i, currentPlayerColor) && !eating) {
									if (currentPlayerColor == Map::RED_PIECE) {
										player1->decreaseCurrentNumberOfPiecesInHand();
									}
									else {
										player2->decreaseCurrentNumberOfPiecesInHand();
									}
									if (map->hasMill(i, currentPlayerColor)) {
										//give current player one turn to remove piece from other player
										audio->play();
										eating = true;
										if (currentPlayerColor == Map::GREEN_PIECE) {
											textBox3->changeText(takePieceText2);
										}
										else {
											textBox3->changeText(takePieceText1);
										}
									}
									else {
										setPlayerTurn();
										didPlayersPlaceAllPiecesOnField();
									}
								}
								break;
							}
						}
					}
				}
			}
		}
		else if (currentState == START_STATE) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				handleSlides();
			}
		}
		else if (currentState == GAMEOVER_STATE) {
			//game is in game over state you cna press r to reset the game
		}
		break;
	case SDL_MOUSEBUTTONUP:
	default:
		break;
	}

}

void Game::handleEating(int piece) {
	/*If current player is RED player and the piece that's selected is GREEN then eat the piece and otherwise...*/
	if (currentPlayerColor == Map::RED_PIECE) {
		if (!map->isPieceRed(piece)) {
			eatPiece(piece);
			player2->decreaseNumberOfPieces();
		}
	}
	else {
		if (map->isPieceRed(piece)) {
			if (eatPiece(piece))
				player1->decreaseNumberOfPieces();
		}
	}
}

bool Game::eatPiece(int piece) {
	if (map->removePiece(piece)) {
		eating = false;
		setPlayerTurn();
		audio2->play();
		audio->pauseSound();
		map->setMillAnimationToFalse();
		return true;
	}
	return false;
}

void Game::didPlayersPlaceAllPiecesOnField() {
	/*When players place all their pieces on the field set moving to true so the players can move their pieces on the field and stop animation of free positions*/
	if (player1->getNumberOfPieces() == 0 && player2->getNumberOfPieces() == 0) {
		moving = true;
		map->stopAnimatedObjects();
	}
}


void Game::handleSlides() {
	int slide = startScreen->getCurrentSlide();
	if (slide == 0) {
		startScreen->setCurrentSlide(1);
	}
	else if (slide == 1) {
		startScreen->setCurrentSlide(2);
	}
	else if (slide == 2) {
		startScreen->setCurrentSlide(3);
	}
	else if (slide == 3) {
		currentState = PLAY_STATE;
	}
}

void Game::setPlayerTurn() {
	if (currentPlayerColor == Map::RED_PIECE) {
		std::string text = "Player 1 pieces: ";
		text += std::to_string(player1->getNumberOfPieces());
		textBox1->changeText(text);
		if (player1->getNumberOfPieces() == 0 && player2->getNumberOfPieces() == 0) {
			textBox3->changeText(movePieceText2);
		}
		else {
			textBox3->changeText(turnText2);
		}
		currentPlayerColor = Map::GREEN_PIECE;
	}
	else {
		std::string text = "Player 2 pieces: ";
		text += std::to_string(player2->getNumberOfPieces());
		textBox2->changeText(text);
		if (player1->getNumberOfPieces() == 0 && player2->getNumberOfPieces() == 0) {
			textBox3->changeText(movePieceText1);
		}
		else {
			textBox3->changeText(turnText1);
		}
		currentPlayerColor = Map::RED_PIECE;
	}
}

void Game::restartPlayerTurn() {
	currentPlayerColor = Map::RED_PIECE;
}

void Game::update() {
	map->update();
	startScreen->update();
	isOver();
 }

void Game::render() {
	SDL_RenderClear(renderer);
	//this is where stuff goes to render
	switch (currentState)
	{
	case START_STATE:
		startScreen->render();
		break;
	case MENU_STATE:
		break;
	case PLAY_STATE:
	case GAMEOVER_STATE:
		map->render();
		textBox1->render();
		textBox2->render();
		textBox3->render();
		break;
	}
	SDL_RenderPresent(renderer);
}


void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	map->clean();
	std::cout << "1..." << std::endl;

	textBox1->clean();
	textBox2->clean();
	textBox3->clean();
	delete player1;
	delete player2;
	startScreen->clean();
	delete audio,audio2;
	std::cout << "Game cleaned..." << std::endl;
}

void Game::isOver() {
	if (player1->getNumberOfPiecesOnBoard() + player1->getNumberOfPieces() < 3) {
		textBox3->changeText(gameover2);
		currentState = GAMEOVER_STATE;
	}
	else if (player2->getNumberOfPiecesOnBoard() + player2->getNumberOfPieces() < 3) {
		textBox3->changeText(gameover1);
		currentState = GAMEOVER_STATE;
	}
}
