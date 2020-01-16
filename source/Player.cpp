#include "Player.h"



Player::Player(const char *color)
{
	currentNumberOfPiecesInHand = maxNumberOfPieces;
}


Player::~Player()
{
}


void Player::decreaseCurrentNumberOfPiecesInHand() {
	currentNumberOfPiecesInHand--;
	piecesOnBoard++;
}

void Player::decreaseNumberOfPieces() {
	piecesOnBoard--;
}


int Player::getNumberOfPieces() {
	return this->currentNumberOfPiecesInHand;
}

int Player::getNumberOfPiecesOnBoard() {
	return this->piecesOnBoard;
}

void Player::reset() {
	this->currentNumberOfPiecesInHand = maxNumberOfPieces;
	this->piecesOnBoard = 0;
}

void Player::increasePiecesOnBoard() {
	this->piecesOnBoard++;
}