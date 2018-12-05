#include "CircleLife.h"
#include <string>
#include <ctime>
// Constructor
CircleLife::CircleLife()
{
	gameOverText = new TextDX();
	isGameOver = false;
	health = 1;
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
	int randomx1;
	int randomx2;
	int randomy1;
	int randomy2;
	srand(time(NULL));
	randomx1 = rand() % (GAME_WIDTH + 1 + 0);
	randomx2 = rand() % (GAME_WIDTH + 1 + 0);
	randomy1 = rand() % (GAME_HEIGHT + 1 + 0);
	randomy2 = rand() % (GAME_HEIGHT + 1 + 0);
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

	if (!obstacle5Texture.initialize(graphics, OBSTACLE5_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle5 texture"));


	// background
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

	//circle
	if (!circle.initialize(this, circleNS::WIDTH, circleNS::HEIGHT, circleNS::COLS, &circleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle"));
	circle.setX(GAME_WIDTH/2);              // start top left
	circle.setY(GAME_HEIGHT/2);
	circle.setEdgeBottom(16);
	circle.setEdgeLeft(16);
	circle.setEdgeRight(16);
	circle.setEdgeTop(16);

	//healthbar
	if (!healthBarBackgroundTexture.initialize(graphics, HEALTHBARBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackground texture"));

	if (!healthBarRedTexture.initialize(graphics, HEALTHBARRED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed texture"));

	if (!healthBarRed.initialize(graphics, 292, 137, 1, &healthBarRedTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed"));

	if (!healthBarBackground.initialize(graphics, 292, 137, 1, &healthBarBackgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackground"));

	healthBarRed.setX(0);
	healthBarRed.setY(0);
	healthBarBackground.setX(0);
	healthBarBackground.setY(0);
	healthBarRed.setScale(0.5f);
	healthBarBackground.setScale(0.5f);

	//obstacle1
	if (!obstacle1.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle1"));
	obstacle1.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle1.setX(GAME_WIDTH);
	obstacle1.setY(randomy1);
	obstacle1.setEdgeLeft(69);
	obstacle1.setEdgeBottom(69);
	obstacle1.setEdgeRight(69);
	obstacle1.setEdgeTop(69);
	obstacle1.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));

	//obstacle2
	if (!obstacle2.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle2"));
	obstacle2.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle2.setX(randomx1);
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
	obstacle3.setY(randomy2);
	obstacle3.setEdgeLeft(69);
	obstacle3.setEdgeBottom(69);
	obstacle3.setEdgeRight(69);
	obstacle3.setEdgeTop(69);
	obstacle3.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));
	
	//obstacle4
	if (!obstacle4.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle4Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle4"));
	obstacle4.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle4.setX(randomx2);
	obstacle4.setY(GAME_HEIGHT);
	obstacle4.setEdgeLeft(69);
	obstacle4.setEdgeBottom(69);
	obstacle4.setEdgeRight(69);
	obstacle4.setEdgeTop(69);
	obstacle4.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));

	//obstacle5
	if (!obstacle5.initialize(this, obstaclesNS::WIDTH, obstaclesNS::HEIGHT, obstaclesNS::TEXTURE_COLS, &obstacle5Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle5"));
	obstacle5.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle5.setX(randomx1);
	obstacle5.setY(GAME_HEIGHT + 100);
	obstacle5.setEdgeLeft(69);
	obstacle5.setEdgeBottom(69);
	obstacle5.setEdgeRight(69);
	obstacle5.setEdgeTop(69);
	obstacle5.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));

	//game over text
	if (gameOverText->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pausedText font"));
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
	//update entities
	circle.update(frameTime);
	obstacle1.updateLeftRight(frameTime);
	obstacle2.updateTopDown(frameTime);
	obstacle3.updateLeftRight(frameTime);
	obstacle4.updateTopDown(frameTime);
	obstacle5.updateRandomObstacles(frameTime);
	healthBarRed.update(frameTime);
	healthBarBackground.update(frameTime);

	if (GetAsyncKeyState(VK_ESCAPE) != 0)
	{
		exitGame();
	}
	else
		return;

	if (health <= 0)
	{
		isGameOver == true;
	}
	else
	{
		health = health - 1;
		isGameOver == false;
	}

}

// Artificial Intelligence
void CircleLife::ai()
{

}
// Handle collisions
void CircleLife::collisions()
{
	VECTOR2 collisionVector;
	if (circle.collidesWith(obstacle1, collisionVector))
		/*|| circle.collidesWith(obstacle2, collisionVector)  
		|| circle.collidesWith(obstacle3, collisionVector) || circle.collidesWith(obstacle4, collisionVector) || circle.collidesWith(obstacle5, collisionVector))
	*/
	{
		//if (obstacle1.PixelPerfectCollision(obstacle1.getSpriteDataRect, circle.getSpriteDataRect) == 1)
			exitGame();
		//else
			//return;
	}
}
// Render game items
void CircleLife::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();                      // add the pictures to the scene
	circle.draw();
	obstacle1.draw();
	obstacle2.draw();
	obstacle3.draw();
	obstacle4.draw();
	obstacle5.draw();
	healthBarBackground.draw();
	healthBarRed.draw();

	if (isGameOver)
	{
		gameOverText->setFontColor(graphicsNS::RED);
		gameOverText->print("Game Over. Press Esc to exit!", GAME_WIDTH / 2, GAME_HEIGHT / 2);
	}
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
	obstacle5Texture.onLostDevice();
	healthBarBackgroundTexture.onLostDevice();
	healthBarRedTexture.onLostDevice();
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
	obstacle5Texture.onResetDevice();
	healthBarBackgroundTexture.onResetDevice();
	healthBarRedTexture.onResetDevice();
	Game::resetAll();
	return;
}

bool CircleLife::checkisGameOver() 
{
	return isGameOver;
}
