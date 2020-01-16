#pragma once

class Player
{
public:
	Player(const char *color);
	~Player();

	void decreaseCurrentNumberOfPiecesInHand();
	void decreaseNumberOfPieces();
	int getNumberOfPieces();
	int getNumberOfPiecesOnBoard();
	void reset();
	void increasePiecesOnBoard();


private:
	const int maxNumberOfPieces = 9;
	int currentNumberOfPiecesInHand;
	int piecesOnBoard = 0;
	const char *color;
};

