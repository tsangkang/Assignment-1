#include "CircleLife.h"
#include <string>

// Constructor
CircleLife::CircleLife()
{
}

// Destructor
CircleLife::~CircleLife()
{
	releaseAll();				// call onLostDevice() for every graphics item
}

// Initializes the game
void CircleLife::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

							// all the textures
	if (!backgroundTexture.initialize(graphics, background_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!circleTexture.initialize(graphics, CIRCLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle texture"));

	if (!obstacle1Texture.initialize(graphics, OBSTACLE1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle1 texture"));


	// background
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	//circle
	if (!circle.initialize(this, circleNS::WIDTH, circleNS::HEIGHT, circleNS::COLS, &circleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle"));

	//obstacle1
	if (!obstacle1.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle1"));

	circle.setX(GAME_WIDTH - (GAME_WIDTH - circleNS::WIDTH));              // start top left
	circle.setY(GAME_HEIGHT - (GAME_HEIGHT - circleNS::HEIGHT));
	obstacle1.setX(GAME_WIDTH - 200);
	obstacle1.setY(GAME_WIDTH - 200);


	return;
}
// Update all game items
void CircleLife::update()
{
	if (input->isKeyDown(CIRCLE_RIGHT_KEY))            // if move right
	{
		circle.setX(circle.getX() + frameTime * CIRCLE_SPEED);
		if ((circle.getX() + circleNS::WIDTH) > GAME_WIDTH)               // stops at the right edge
			circle.setX(GAME_WIDTH - circle.getWidth());  // prevents from moving over the edge
	}
	if (input->isKeyDown(CIRCLE_LEFT_KEY))             // if move left
	{
		circle.setX(circle.getX() - frameTime * CIRCLE_SPEED);
		if ((circle.getX() - circleNS::WIDTH) < -circle.getWidth())         // stops at the left edge
			circle.setX(circle.getWidth()- circleNS::WIDTH);      // prevents from moving over the edge
	}
	if (input->isKeyDown(CIRCLE_UP_KEY))               // if move up
	{
		circle.setY(circle.getY() - frameTime * CIRCLE_SPEED);
		if ((circle.getY() - circleNS::HEIGHT) < -circle.getHeight())        // stops at the top edge
			circle.setY(0);								 // prevents from moving over the edge
	}
	if (input->isKeyDown(CIRCLE_DOWN_KEY))             // if move down
	{
		circle.setY(circle.getY() + frameTime * CIRCLE_SPEED);
		if ((circle.getY() + circleNS::HEIGHT) > GAME_HEIGHT)              // if off screen bottom
			circle.setY(GAME_HEIGHT- circleNS::HEIGHT);    // position off screen top
	}
	circle.update(frameTime);
	obstacle1.update(frameTime);
}

// Artificial Intelligence
void CircleLife::ai()
{

}
// Handle collisions
void CircleLife::collisions()
{

}
// Render game items
void CircleLife::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();                      // add the orion background to the scene
	circle.draw();
	obstacle1.draw();
	graphics->spriteEnd();                  // end drawing sprites
}
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset
void CircleLife::releaseAll()
{
	backgroundTexture.onLostDevice();
	circleTexture.onLostDevice();
	obstacle1Texture.onLostDevice();
	Game::releaseAll();
	return;
}
// The graphics device has been reset.
// Recreate all surfaces
void CircleLife::resetAll()
{
	backgroundTexture.onResetDevice();
	circleTexture.onResetDevice();
	obstacle1Texture.onResetDevice();
	Game::resetAll();
	return;
}