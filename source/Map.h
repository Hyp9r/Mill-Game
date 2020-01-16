#pragma once
#include "TextureManager.h"
#include "Game.h"
#include "AnimatedObject.h"
#include <list>
class Map
{
public:
	Map();
	~Map();

	enum PieceType{RED_PIECE = 1, GREEN_PIECE = 2};
	bool placePiece(int position, PieceType pieceType);
	bool movePiece(int positionToMoveAt, int lastPosition, PieceType pieceType);
	bool removePiece(int position);
	void removeAllPieces();
	void update();
	void render();
	void clean();
	bool isPositionEmpty(int row, int column);
	bool isPositionEmpty(int position);
	bool isPieceRed(int row, int column);
	bool isPieceRed(int position);
	SDL_Rect *getPositionRects();
	int getPosition(SDL_Rect rect);
	std::list<int> getPosiblePositions(int position);
	void stopAnimatedObjects();
	void startAnimatedObjects();
	void animateAvaliablePositions(std::list<int> positions);
	void resetAnimatingAvaliablePositions();
	Map::PieceType checkColor(int position);
	bool hasMill(int position, Map::PieceType color);
	void setMillAnimationToFalse() {
		animateMill = false;
	}

private:
	int map[8][3] = { 
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};

	SDL_Rect positionSrcRect = { 0, 0, 40, 40 };
	SDL_Rect positionDestRects[24] = { {80, 80, 40, 40}, {380, 80, 40,40}, {680,80,40,40}, {180,180,40,40}, 
	{380,180,40,40}, {580,180,40,40}, {280,230,40,40}, {380,230,40,40}, {480,230,40,40}, {80,295,40,40}, 
	{180,295,40,40}, {280,295,40,40}, {480,295,40,40}, {580,295,40,40}, {680,295,40,40}, {280,380,40,40},
	{380,380,40,40}, {480,380,40,40}, {180,430,40,40}, {380,430,40,40}, {580,430,40,40}, {80,530,40,40},
	{380,530,40,40}, {680,530,40,40}};

	SDL_Rect helperSrcRect = { 0, 0, 60, 60 };
	SDL_Rect helperDestRects[24] = { {70, 70, 60, 60}, {370, 70, 60,60}, {670,70,60,60}, {170,170,60,60},
	{370,170,60,60}, {570,170,60,60}, {270,220,60,60}, {370,220,60,60}, {470,220,60,60}, {70,285,60,60},
	{170,285,60,60}, {270,285,60,60}, {470,285,60,60}, {570,285,60,60}, {670,285,60,60}, {270,370,60,60},
	{370,370,60,60}, {470,370,60,60}, {170,420,60,60}, {370,420,60,60}, {570,420,60,60}, {70,520,60,60},
	{370,520,60,60}, {670,520,60,60} };;
	

	SDL_Rect mapSrcRect = {0,0, 800, 600};
	SDL_Rect mapDestRect = { 0,0, 800, 600 };

	SDL_Texture *texture = TextureManager::LoadTexture("assets/map.png");
	SDL_Texture *textureRed = TextureManager::LoadTexture("assets/player.png");
	SDL_Texture *textureGreen = TextureManager::LoadTexture("assets/green.png");
	AnimatedObject *animatedObjects[24];
	AnimatedObject *millAnimation;
	AnimatedObject *millAnimation1;
	AnimatedObject *millAnimation2;
	bool animate = true;
	bool animateMill = false;
	int positionsToAnimate[24] = { 0 };
};

