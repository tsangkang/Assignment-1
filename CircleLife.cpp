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
	Game::timeStart;
							// all the textures
	if (!backgroundTexture.initialize(graphics, background_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!circleTexture.initialize(graphics, CIRCLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle texture"));

	if (!obstacle1Texture.initialize(graphics, OBSTACLE1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle1 texture"));

	if (!obstacle2Texture.initialize(graphics, OBSTACLE2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle2 texture"));

	if (!obstacle3Texture.initialize(graphics, OBSTACLE3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle3 texture"));

	if (!obstacle4Texture.initialize(graphics, OBSTACLE4_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle4 texture"));


	// background
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	//circle
	if (!circle.initialize(this, circleNS::WIDTH, circleNS::HEIGHT, circleNS::COLS, &circleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle"));
	circle.setX(GAME_WIDTH - (GAME_WIDTH - circleNS::WIDTH));              // start top left
	circle.setY(GAME_HEIGHT - (GAME_HEIGHT - circleNS::HEIGHT));
	circle.setEdgeBottom(16);
	circle.setEdgeLeft(16);
	circle.setEdgeRight(16);
	circle.setEdgeTop(16);

	//obstacle1
	if (!obstacle1.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle1"));
	obstacle1.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle1.setX(GAME_WIDTH);
	obstacle1.setY(GAME_HEIGHT - 200);
	obstacle1.setEdgeLeft(69);
	obstacle1.setEdgeBottom(69);
	obstacle1.setEdgeRight(69);
	obstacle1.setEdgeTop(69);
	obstacle1.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));

	//obstacle2
	if (!obstacle2.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle2"));
	obstacle2.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle2.setX(GAME_WIDTH - 500);
	obstacle2.setY(0);
	obstacle2.setEdgeLeft(69);
	obstacle2.setEdgeBottom(69);
	obstacle2.setEdgeRight(69);
	obstacle2.setEdgeTop(69);
	obstacle2.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));
	
	//obstacle3
	if (!obstacle3.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle3Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle3"));
	obstacle3.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle3.setX(0);
	obstacle3.setY(GAME_HEIGHT/3);
	obstacle3.setEdgeLeft(69);
	obstacle3.setEdgeBottom(69);
	obstacle3.setEdgeRight(69);
	obstacle3.setEdgeTop(69);
	obstacle3.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));
	
	//obstacle4
	if (!obstacle4.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle4Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle4"));
	obstacle4.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle4.setX(GAME_WIDTH/3);
	obstacle4.setY(GAME_HEIGHT);
	obstacle4.setEdgeLeft(69);
	obstacle4.setEdgeBottom(69);
	obstacle4.setEdgeRight(69);
	obstacle4.setEdgeTop(69);
	obstacle4.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));
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
			circle.setX(circle.getWidth() - circleNS::WIDTH);      // prevents from moving over the edge
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
			circle.setY(GAME_HEIGHT - circleNS::HEIGHT);    // position off screen top
	}
	circle.update(frameTime);
	obstacle1.updateLeftRight(frameTime);
	obstacle2.updateTopDown(frameTime);
	obstacle3.updateLeftRight(frameTime);
	obstacle4.updateTopDown(frameTime);

	if (GetAsyncKeyState(VK_ESCAPE) != 0)
	{
		exitGame();
	}
	else
		return;
}

// Artificial Intelligence
void CircleLife::ai()
{

}
// Handle collisions
void CircleLife::collisions()
{
	VECTOR2 collisionVector;
	if (circle.collidesWith(obstacle1, collisionVector) || circle.collidesWith(obstacle2, collisionVector)  
		|| circle.collidesWith(obstacle3, collisionVector) || circle.collidesWith(obstacle4, collisionVector))
	{
		exitGame();
		/*if (obstacle1.PixelPerfectCollision(obstacle1.getSpriteDataRect, circle.getSpriteDataRect) == 1)
			exitGame();
		else
			return;*/
	}
}
// Render game items
void CircleLife::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();                      // add the orion background to the scene
	circle.draw();
	obstacle1.draw();
	obstacle2.draw();
	obstacle3.draw();
	obstacle4.draw();
	graphics->spriteEnd();                  // end drawing sprites
}
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset
void CircleLife::releaseAll()
{
	backgroundTexture.onLostDevice();
	circleTexture.onLostDevice();
	obstacle1Texture.onLostDevice();
	obstacle2Texture.onLostDevice();
	obstacle3Texture.onLostDevice();
	obstacle4Texture.onLostDevice();
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
	obstacle2Texture.onResetDevice();
	obstacle3Texture.onResetDevice();
	obstacle4Texture.onResetDevice();
	Game::resetAll();
	return;
}
