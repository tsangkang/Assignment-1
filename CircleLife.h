#pragma once
#ifndef _CircleLife_H			// prevent multiple definitions if this
#define _CircleLife_H			// .. file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#include "game.h"
#include "textureManager.h"
#include "image.h"


// class declaration to be inserted here

#endif

class CircleLife : public Game
{
private:
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager planetTexture;   // planet texture
	TextureManager shipTexture;     // ship texture
	Image   planet;                 // planet image
	Image   nebula;                 // nebula image
	Image   ship;                   // ship image

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