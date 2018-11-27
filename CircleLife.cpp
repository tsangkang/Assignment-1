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

							// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//ship
	if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	ship.setX(GAME_WIDTH / 4);              // start above and left of planet
	ship.setY(GAME_HEIGHT / 4);


	return;
}
// Update all game items
void CircleLife::update()
{
	if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	{
		ship.setX(ship.getX() + frameTime * SHIP_SPEED);
		if (ship.getX() > GAME_WIDTH)               // if off screen right
			ship.setX((float)-ship.getWidth());  // position off screen left
	}
	if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	{
		ship.setX(ship.getX() - frameTime * SHIP_SPEED);
		if (ship.getX() < -ship.getWidth())         // if off screen left
			ship.setX((float)GAME_WIDTH);      // position off screen right
	}
	if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	{
		ship.setY(ship.getY() - frameTime * SHIP_SPEED);
		if (ship.getY() < -ship.getHeight())        // if off screen top
			ship.setY((float)GAME_HEIGHT);     // position off screen bottom
	}
	if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	{
		ship.setY(ship.getY() + frameTime * SHIP_SPEED);
		if (ship.getY() > GAME_HEIGHT)              // if off screen bottom
			ship.setY((float)-ship.getHeight());    // position off screen top
	}

	ship.update(frameTime);

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

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	ship.draw();

	graphics->spriteEnd();                  // end drawing sprites
}
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset
void CircleLife::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	shipTexture.onLostDevice();
	Game::releaseAll();
	return;
}
// The graphics device has been reset.
// Recreate all surfaces
void CircleLife::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	shipTexture.onResetDevice();
	Game::resetAll();
	return;
}