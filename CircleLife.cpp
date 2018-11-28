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

							// background texture
	if (!backgroundTexture.initialize(graphics, background_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	if (!circleTexture.initialize(graphics, CIRCLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));


	// background
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//circle
	if (!circle.initialize(this, circleNS::WIDTH, circleNS::HEIGHT, circleNS::COLS, &circleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	circle.setX(GAME_WIDTH - (GAME_WIDTH - circleNS::WIDTH));              // start above and left of planet
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
	planet.draw();                          // add the planet to the scene
	circle.draw();
	obstacle1.draw();
	graphics->spriteEnd();                  // end drawing sprites
}
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset
void CircleLife::releaseAll()
{
	planetTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	circleTexture.onLostDevice();
	Game::releaseAll();
	return;
}
// The graphics device has been reset.
// Recreate all surfaces
void CircleLife::resetAll()
{
	backgroundTexture.onResetDevice();
	planetTexture.onResetDevice();
	circleTexture.onResetDevice();
	Game::resetAll();
	return;
}