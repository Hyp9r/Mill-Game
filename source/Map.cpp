#include "Map.h"
#include <list>



Map::Map()
{
	for (int i = 0; i < 24; i++) {
		animatedObjects[i] = new AnimatedObject("assets/helper.png", 3, 600, helperSrcRect, helperDestRects[i]);
	}
	millAnimation = new AnimatedObject("assets/mill_animation.png", 3, 100, helperSrcRect);
	millAnimation1 = new AnimatedObject("assets/mill_animation.png", 3, 100, helperSrcRect);
	millAnimation2 = new AnimatedObject("assets/mill_animation.png", 3, 100, helperSrcRect);

}


Map::~Map()
{
}

bool Map::placePiece(int position, PieceType pieceType) {
	int row = (position / 3);
	int column = position % 3;
	if (map[row][column] == 0) {
		map[row][column] = pieceType;
		return true;
	}
	return false;
}


bool Map::removePiece(int position) {
	int row = (position / 3);
	int column = position % 3;
	if (map[row][column] == 0) {
		return false;
	}
	map[row][column] = 0;
	return true;
}

void Map::removeAllPieces() {
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 3; column++) {
			map[row][column] = 0;
		}
	}
}

bool Map::isPositionEmpty(int row, int column) {
	if (map[row][column] != 0) {
		return false;
	}
	return true;
}

bool Map::isPositionEmpty(int position) {
	int row = position / 3;
	int column = position % 3;
	if (map[row][column] == 0) {
		return true;
	}
	return false;
}

bool Map::isPieceRed(int row, int column) {
	if (map[row][column] == Map::RED_PIECE) {
		return true;
	}
	return false;
}

bool Map::isPieceRed(int position) {
	int row = (position / 3);
	int column = position % 3;
	if (map[row][column] == Map::RED_PIECE) {
		return true;
	}
	return false;
}


void Map::update() {
	for (int i = 0; i < 24; i++) {
		animatedObjects[i]->update();
	}
	millAnimation->update();
	millAnimation1->update();
	millAnimation2->update();
}

void Map::render() {
	SDL_RenderCopy(Game::renderer, texture, &mapSrcRect, &mapDestRect);
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 3; column++) {
			int position = (row * 3) + column;
			if (isPositionEmpty(row, column) && animate) {
				animatedObjects[position]->render();
			}

			if (positionsToAnimate[position] == 1 && map[row][column] == 0) {
				animatedObjects[position]->render();
			}
			if (animateMill) {
				millAnimation->render();
				millAnimation1->render();
				millAnimation2->render();

			}

			if (!isPositionEmpty(row, column)) {
				if (isPieceRed(row, column)) {
					SDL_RenderCopy(Game::renderer, textureRed, &positionSrcRect, &positionDestRects[position]);
				}
				else {
					SDL_RenderCopy(Game::renderer, textureGreen, &positionSrcRect, &positionDestRects[position]);
				}
			}
		}
	}
}

void Map::clean() {
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(textureRed);
	SDL_DestroyTexture(textureGreen);
	//delete[] &animatedObjects;
	delete millAnimation, millAnimation1, millAnimation2;
}

SDL_Rect *Map::getPositionRects() {
	return helperDestRects;
}

int Map::getPosition(SDL_Rect rect) {
	int counter = 0;
	for (int i = 0; i < 24; i++) {
		if (positionDestRects[i].x == rect.x && positionDestRects[i].y == rect.y) {
			std::cout << " u loopu" << std::endl;
			counter = i;
			break;
		}
	}
	return counter;
}

bool Map::hasMill(int position, Map::PieceType color) {
	millAnimation->setPosition(helperDestRects[position]);
	/*Positions variable is here to store which pieces were involved in creation of mill*/
	bool result = false;
	switch (position)
	{
	case 0:
		if (map[0][1] == color && map[0][2] == color) {
			int rect2[2] = { 0, 2 };
			millAnimation1->setPosition(helperDestRects[1]);
			millAnimation2->setPosition(helperDestRects[2]);
			result = true;
		}
		else if (map[3][0] == color && map[7][0] == color) {
			millAnimation1->setPosition(helperDestRects[9]);
			millAnimation2->setPosition(helperDestRects[21]);
			result = true;
		}
		break;
	case 1:
		if (map[0][0] == color && map[0][2] == color) {
			millAnimation1->setPosition(helperDestRects[0]);
			millAnimation2->setPosition(helperDestRects[2]);
			result = true;
		}
		else if (map[1][1] == color && map[2][1] == color) {
			millAnimation1->setPosition(helperDestRects[4]);
			millAnimation2->setPosition(helperDestRects[7]);
			result = true;
		}
		break;
	case 2:
		if (map[0][0] == color && map[0][1] == color) {
			millAnimation1->setPosition(helperDestRects[0]);
			millAnimation2->setPosition(helperDestRects[1]);
			result = true;
		}
		else if (map[4][2] == color && map[7][2] == color) {
			millAnimation1->setPosition(helperDestRects[14]);
			millAnimation2->setPosition(helperDestRects[23]);
			result = true;
		}
		break;
	case 3:
		if (map[1][1] == color && map[1][2] == color) {
			millAnimation1->setPosition(helperDestRects[4]);
			millAnimation2->setPosition(helperDestRects[5]);
			result = true;
		}
		else if (map[3][1] == color && map[6][0] == color) {
			millAnimation1->setPosition(helperDestRects[10]);
			millAnimation2->setPosition(helperDestRects[18]);
			result = true;
		}
		break;
	case 4:
		if (map[1][0] == color && map[1][2] == color) {
			millAnimation1->setPosition(helperDestRects[3]);
			millAnimation2->setPosition(helperDestRects[5]);
			result = true;
		}
		else if (map[0][1] == color && map[2][1] == color) {
			millAnimation1->setPosition(helperDestRects[7]);
			millAnimation2->setPosition(helperDestRects[1]);
			result = true;
		}
		break;
	case 5:
		if (map[1][0] == color && map[1][1] == color) {
			millAnimation1->setPosition(helperDestRects[3]);
			millAnimation2->setPosition(helperDestRects[4]);
			result = true;
		}
		else if (map[4][1] == color && map[6][2] == color) {
			millAnimation1->setPosition(helperDestRects[13]);
			millAnimation2->setPosition(helperDestRects[20]);
			result = true;
		}
		break;
	case 6:
		if (map[2][1] == color && map[2][2] == color) {
			millAnimation1->setPosition(helperDestRects[7]);
			millAnimation2->setPosition(helperDestRects[8]);
			result = true;
		}
		else if (map[3][2] == color && map[5][0] == color) {
			millAnimation1->setPosition(helperDestRects[11]);
			millAnimation2->setPosition(helperDestRects[15]);
			result = true;
		}
		break;
	case 7:
		if (map[2][0] == color && map[2][2] == color) {
			millAnimation1->setPosition(helperDestRects[6]);
			millAnimation2->setPosition(helperDestRects[8]);
			result = true;
		}
		else if (map[0][1] == color && map[1][1] == color) {
			millAnimation1->setPosition(helperDestRects[1]);
			millAnimation2->setPosition(helperDestRects[4]);
			result = true;
		}
		break;
	case 8:
		if (map[2][0] == color && map[2][1] == color) {
			millAnimation1->setPosition(helperDestRects[6]);
			millAnimation2->setPosition(helperDestRects[7]);
			result = true;
		}
		else if (map[4][0] == color && map[5][2] == color) {
			millAnimation1->setPosition(helperDestRects[12]);
			millAnimation2->setPosition(helperDestRects[17]);
			result = true;
		}
		break;
	case 9:
		if (map[3][1] == color && map[3][2] == color) {
			millAnimation1->setPosition(helperDestRects[10]);
			millAnimation2->setPosition(helperDestRects[11]);
			result = true;
		}
		else if (map[0][0] == color && map[7][0] == color) {
			millAnimation1->setPosition(helperDestRects[0]);
			millAnimation2->setPosition(helperDestRects[21]);
			result = true;
		}
		break;
	case 10:
		if (map[1][0] == color && map[6][0] == color) {
			millAnimation1->setPosition(helperDestRects[3]);
			millAnimation2->setPosition(helperDestRects[18]);
			result = true;
		}
		else if (map[3][0] == color && map[3][2] == color) {
			millAnimation1->setPosition(helperDestRects[9]);
			millAnimation2->setPosition(helperDestRects[11]);
			result = true;
		}
		break;
	case 11:
		if (map[3][0] == color && map[3][1] == color) {
			millAnimation1->setPosition(helperDestRects[9]);
			millAnimation2->setPosition(helperDestRects[10]);
			result = true;
		}
		else if (map[2][0] == color && map[5][0] == color) {
			millAnimation1->setPosition(helperDestRects[6]);
			millAnimation2->setPosition(helperDestRects[15]);
			result = true;
		}
		break;
	case 12:
		if (map[4][1] == color && map[4][2] == color) {
			millAnimation1->setPosition(helperDestRects[13]);
			millAnimation2->setPosition(helperDestRects[14]);
			result = true;
		}
		else if (map[2][2] == color && map[5][2] == color) {
			millAnimation1->setPosition(helperDestRects[8]);
			millAnimation2->setPosition(helperDestRects[17]);
			result = true;
		}
		break;
	case 13:
		if (map[4][0] == color && map[4][2] == color) {
			millAnimation1->setPosition(helperDestRects[12]);
			millAnimation2->setPosition(helperDestRects[14]);
			result = true;
		}
		else if (map[1][2] == color && map[6][2] == color) {
			millAnimation1->setPosition(helperDestRects[5]);
			millAnimation2->setPosition(helperDestRects[20]);
			result = true;
		}
		break;
	case 14:
		if (map[4][0] == color && map[4][1] == color) {
			millAnimation1->setPosition(helperDestRects[12]);
			millAnimation2->setPosition(helperDestRects[13]);
			result = true;
		}
		else if (map[0][2] == color && map[7][2] == color) {
			millAnimation1->setPosition(helperDestRects[2]);
			millAnimation2->setPosition(helperDestRects[23]);
			result = true;
		}
		break;
	case 15:
		if (map[5][1] == color && map[5][2] == color) {
			millAnimation1->setPosition(helperDestRects[16]);
			millAnimation2->setPosition(helperDestRects[17]);
			result = true;
		}
		else if (map[2][0] == color && map[3][2] == color) {
			millAnimation1->setPosition(helperDestRects[6]);
			millAnimation2->setPosition(helperDestRects[11]);
			result = true;
		}
		break;
	case 16:
		if (map[5][0] == color && map[5][2] == color) {
			millAnimation1->setPosition(helperDestRects[15]);
			millAnimation2->setPosition(helperDestRects[17]);
			result = true;
		}
		else if (map[6][1] == color && map[7][1] == color) {
			millAnimation1->setPosition(helperDestRects[19]);
			millAnimation2->setPosition(helperDestRects[22]);
			result = true;
		}
		break;
	case 17:
		if (map[5][0] == color && map[5][1] == color) {
			millAnimation1->setPosition(helperDestRects[15]);
			millAnimation2->setPosition(helperDestRects[16]);
			result = true;
		}
		else if (map[4][0] == color && map[2][2] == color) {
			millAnimation1->setPosition(helperDestRects[12]);
			millAnimation2->setPosition(helperDestRects[8]);
			result = true;
		}
		break;
	case 18:
		if (map[6][1] == color && map[6][2] == color) {
			millAnimation1->setPosition(helperDestRects[19]);
			millAnimation2->setPosition(helperDestRects[20]);
			result = true;
		}
		else if (map[1][0] == color && map[3][1] == color) {
			millAnimation1->setPosition(helperDestRects[3]);
			millAnimation2->setPosition(helperDestRects[10]);
			result = true;
		}
		break;
	case 19:
		if (map[6][0] == color && map[6][2] == color) {
			millAnimation1->setPosition(helperDestRects[18]);
			millAnimation2->setPosition(helperDestRects[20]);
			result = true;
		}
		else if (map[7][1] == color && map[5][1] == color) {
			millAnimation1->setPosition(helperDestRects[22]);
			millAnimation2->setPosition(helperDestRects[16]);
			result = true;
		}
		break;
	case 20:
		if (map[6][0] == color && map[6][1] == color) {
			millAnimation1->setPosition(helperDestRects[18]);
			millAnimation2->setPosition(helperDestRects[19]);
			result = true;
		}
		else if (map[1][2] == color && map[4][1] == color) {
			millAnimation1->setPosition(helperDestRects[4]);
			millAnimation2->setPosition(helperDestRects[13]);
			result = true;
		}
		break;
	case 21:
		if (map[7][1] == color && map[7][2] == color) {
			millAnimation1->setPosition(helperDestRects[22]);
			millAnimation2->setPosition(helperDestRects[23]);
			result = true;
		}
		else if (map[0][0] == color && map[3][0] == color) {
			millAnimation1->setPosition(helperDestRects[0]);
			millAnimation2->setPosition(helperDestRects[9]);
			result = true;
		}
		break;
	case 22:
		if (map[7][0] == color && map[7][2] == color) {
			millAnimation1->setPosition(helperDestRects[21]);
			millAnimation2->setPosition(helperDestRects[23]);
			result = true;
		}
		else if (map[5][1] == color && map[6][1] == color) {
			millAnimation1->setPosition(helperDestRects[16]);
			millAnimation2->setPosition(helperDestRects[19]);
			result = true;
		}
		break;
	case 23:
		if (map[7][0] == color && map[7][1] == color) {
			millAnimation1->setPosition(helperDestRects[21]);
			millAnimation2->setPosition(helperDestRects[22]);
			result = true;
		}
		else if (map[0][2] == color && map[4][2] == color) {
			millAnimation1->setPosition(helperDestRects[2]);
			millAnimation2->setPosition(helperDestRects[14]);
			result = true;
		}
		break;
	}
	if (result) {
		animateMill = true;
	}
	return result;
}

std::list<int> Map::getPosiblePositions(int position) {
	std::list<int> posiblePositions;
	switch (position) {
	case 0:
		posiblePositions = { 1, 9 };
		break;
	case 1:
		posiblePositions = { 0, 2, 4 };
		break;
	case 2:
		posiblePositions = { 1, 14 };
		break;
	case 3:
		posiblePositions = { 4, 10 };
		break;
	case 4:
		posiblePositions = { 3, 1, 5, 7 };
		break;
	case 5:
		posiblePositions = { 4, 13 };
		break;
	case 6:
		posiblePositions = { 7, 11 };
		break;
	case 7:
		posiblePositions = { 6, 8, 4 };
		break;
	case 8:
		posiblePositions = { 7, 12 };
		break;
	case 9:
		posiblePositions = { 0, 10, 21 };
		break;
	case 10:
		posiblePositions = { 11 , 9, 3, 18 };
		break;
	case 11:
		posiblePositions = { 10, 6, 15 };
		break;
	case 12:
		posiblePositions = { 8, 17, 13 };
		break;
	case 13:
		posiblePositions = { 12, 5, 20, 14 };
		break;
	case 14:
		posiblePositions = { 13, 2, 23 };
		break;
	case 15:
		posiblePositions = { 11, 16 };
		break;
	case 16:
		posiblePositions = { 15, 17, 19 };
		break;
	case 17:
		posiblePositions = { 16, 12 };
		break;
	case 18:
		posiblePositions = { 10, 19 };
		break;
	case 19:
		posiblePositions = { 16, 18, 20, 22 };
		break;
	case 20:
		posiblePositions = { 19, 13 };
		break;
	case 21:
		posiblePositions = { 22, 9 };
		break;
	case 22:
		posiblePositions = { 19, 21, 23 };
		break;
	case 23:
		posiblePositions = { 14, 22 };
		break;
	}
	return posiblePositions;
}


void Map::stopAnimatedObjects() {
	animate = false;
}

void Map::startAnimatedObjects() {
	animate = true;
}

void Map::animateAvaliablePositions(std::list<int> positions) {
	for (std::list<int>::iterator i = positions.begin(); i != positions.end(); i++) {
		positionsToAnimate[*i] = 1;
	}
}


void Map::resetAnimatingAvaliablePositions() {
	for (int i = 0; i < 24; i++) {
		positionsToAnimate[i] = 0;
	}
}

Map::PieceType Map::checkColor(int position) {
	int row = position / 3;
	int column = position % 3;
	if (map[row][column] == Map::GREEN_PIECE) {
		return Map::GREEN_PIECE;
	}
	return Map::RED_PIECE;
}