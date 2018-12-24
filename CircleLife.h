//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#pragma once
#ifndef _CircleLife_H			// prevent multiple definitions if this
#define _CircleLife_H			// .. file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "circle.h"
#include "obstacles.h"
#include "TextDX.h"
#include "heart.h"
#include "obstaclesLR.h"
#include "obstaclesUD.h"

// class declaration to be inserted here

#endif

class CircleLife : public Game
{
private:
	// game items
	TextureManager backgroundTexture;   // background texture
	TextureManager circleTexture;     // circle texture
/*	TextureManager obstacle1Texture;
	TextureManager obstacle2Texture;
	TextureManager obstacle3Texture;
	TextureManager obstacle4Texture;
	TextureManager obstacle5Texture;*/
	TextureManager obstacleTexture;
	TextureManager heartTexture;
	Image   background;                 // background image
	Circle   circle;                   // circle image

	Obstacles obstacle;
	TextDX *gameOverText;

	Heart heartList[MAX_HEART_NO];
	ObstaclesLR obstaclesLRList[MAX_OBSTACLES_LR_NO];	
	ObstaclesUD obstaclesUDList[MAX_OBSTACLES_UD_NO];


	int health;
	int numOfHits = 0;


public:
	// Constructor
	CircleLife();
	// Destructor
	virtual ~CircleLife();

	// Initialize the game
	void update();		// must override pure virtual from Game
	void ai();			// ""
	void collisions();



	void CircleLife::initialize(HWND hwnd);
	

	void CircleLife::render();

	void CircleLife::releaseAll();

	void CircleLife::resetAll();

};