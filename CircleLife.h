#pragma once
#ifndef _CircleLife_H			// prevent multiple definitions if this
#define _CircleLife_H			// .. file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "circle.h"
#include "obstacles.h"


// class declaration to be inserted here

#endif

class CircleLife : public Game
{
private:
	// game items
	TextureManager backgroundTexture;   // background texture
	TextureManager circleTexture;     // circle texture
	TextureManager obstacle1Texture;
	TextureManager obstacle2Texture;
	TextureManager obstacle3Texture;
	TextureManager obstacle4Texture;
	Image   background;                 // background image
	Circle   circle;                   // circle image
	Obstacles obstacle1;
	Obstacles obstacle2;
	Obstacles obstacle3;
	Obstacles obstacle4;

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