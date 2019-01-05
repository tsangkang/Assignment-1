//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#include "CircleLife.h"
#include <string>
#include <ctime>
// Constructor
CircleLife::CircleLife()
{
	gameOverText = new TextDX();

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
	srand(time(NULL));
							// all the textures
	if (!backgroundTexture.initialize(graphics, background_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!circleTexture.initialize(graphics, CIRCLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle texture"));

/*	if (!obstacle1Texture.initialize(graphics, OBSTACLE1_IMAGE))       preliminary obstacles
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle1 texture"));

	if (!obstacle2Texture.initialize(graphics, OBSTACLE2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle2 texture"));

	if (!obstacle3Texture.initialize(graphics, OBSTACLE3_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle3 texture"));

	if (!obstacle4Texture.initialize(graphics, OBSTACLE4_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle4 texture"));

	if (!obstacle5Texture.initialize(graphics, OBSTACLE5_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle5 texture"));*/

	if (!obstacleTexture.initialize(graphics, OBSTACLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));


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

	/*//obstacle1
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
	obstacle5.setVelocity(VECTOR2(obstaclesNS::SPEED, -obstaclesNS::SPEED));*/

	for (int i = 0; i < MAX_OBSTACLES_LR_NO; i++)
	{
		if (!obstaclesLRList[i].initialize(this, obstaclesBounceNS::WIDTH, obstaclesBounceNS::HEIGHT, obstaclesBounceNS::TEXTURE_COLS, &obstacleTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player ship"));
		obstaclesLRList[i].setFrames(obstaclesBounceNS::START_FRAME, obstaclesBounceNS::END_FRAME);
		obstaclesLRList[i].setCurrentFrame(obstaclesBounceNS::START_FRAME);
		obstaclesLRList[i].setX(0);
		obstaclesLRList[i].setVelocity(VECTOR2(-obstaclesBounceNS::SPEED, 0));
		//obstaclesLRList[i].setRadians(-obstaclesBounceNS::ROTATION_RATE * 2); //for rotation
		obstaclesLRList[i].setY(rand() % (GAME_HEIGHT - obstaclesNS::HEIGHT));
	}

	for (int i = 0; i < MAX_OBSTACLES_LR_NO; i++)
	{
		if (!obstaclesUDList[i].initialize(this, obstaclesBounceNS::WIDTH, obstaclesBounceNS::HEIGHT, obstaclesBounceNS::TEXTURE_COLS, &obstacleTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player ship"));
		obstaclesUDList[i].setFrames(obstaclesBounceNS::START_FRAME, obstaclesBounceNS::END_FRAME);
		obstaclesUDList[i].setCurrentFrame(obstaclesBounceNS::START_FRAME);
		obstaclesUDList[i].setX(rand() % (GAME_WIDTH - obstaclesNS::WIDTH));
		obstaclesUDList[i].setVelocity(VECTOR2(0, -obstaclesBounceNS::SPEED));
		//obstaclesUDList[i].setRadians(-obstaclesBounceNS::ROTATION_RATE * 2); //for rotation
		obstaclesUDList[i].setY(0);
	}

	for (int i = 0; i < MAX_OBSTACLES_NO; i++)
	{
		if (!obstaclesFlyInList[i].initialize(this, obstaclesBounceNS::WIDTH, obstaclesBounceNS::HEIGHT, obstaclesBounceNS::TEXTURE_COLS, &obstacleTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player ship"));
		obstaclesFlyInList[i].setFrames(obstaclesBounceNS::START_FRAME, obstaclesBounceNS::END_FRAME);
		obstaclesFlyInList[i].setCurrentFrame(obstaclesBounceNS::START_FRAME);
		obstaclesFlyInList[i].setX(GAME_WIDTH - obstaclesNS::WIDTH);
		obstaclesFlyInList[i].setVelocity(VECTOR2(-obstaclesBounceNS::SPEED, 0));
		//obstaclesFlyInList[i].setRadians(-obstaclesBounceNS::ROTATION_RATE * 2); //for rotation
		obstaclesFlyInList[i].setY(rand() % (GAME_HEIGHT - obstaclesNS::HEIGHT));
	}

	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));

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


	for (int i = 0; i < MAX_OBSTACLES_LR_NO; i++)
	{
		obstaclesLRList[i].updateLeftRight(frameTime);
	}

	for (int i = 0; i < MAX_OBSTACLES_LR_NO; i++)
	{
		obstaclesUDList[i].updateUpDown(frameTime);
	}

	for (int i = 0; i < MAX_OBSTACLES_NO; i++)
	{
		obstaclesFlyInList[i].update(frameTime);
	}
	for (int i = 0; i < MAX_HEART_NO; i++)
	{
		if (!heartList[i].initialize(this, heartNS::WIDTH, heartNS::HEIGHT, heartNS::TEXTURE_COLS, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart "));
		heartList[i].setFrames(heartNS::HEART_START_FRAME, heartNS::HEART_END_FRAME);
		heartList[i].setCurrentFrame(heartNS::HEART_START_FRAME);
		heartList[i].setDegrees(0);
		heartList[i].setX(GAME_WIDTH / 20 * (MAX_HEART_NO - i));
		heartList[i].setY(GAME_HEIGHT / 18);
		heartList[i].setScale(heartNS::MAX_HEART_SCALE);
	}

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
	for (int i = 0; i < MAX_OBSTACLES_NO; i++)
	{
		if (circle.collidesWith(obstaclesLRList[i], collisionVector))
		{
			obstaclesLRList[i].setScale(0);
			obstaclesLRList[i].setActive(false);
			if (numOfHits < MAX_HEART_NO)
			{
				numOfHits++;
			}
		}
		else if (circle.collidesWith(obstaclesLRList[i], collisionVector))
		{
			obstaclesLRList[i].setScale(0);
			obstaclesLRList[i].setActive(false);
				if (numOfHits < MAX_HEART_NO)
				{
					numOfHits++;
				}
		}
		
		else if (circle.collidesWith(obstaclesFlyInList[i], collisionVector))
		{
			obstaclesFlyInList[i].setScale(0);
			obstaclesFlyInList[i].setActive(false);
			if (numOfHits < MAX_HEART_NO)
			{
				numOfHits++;
			}
		}
	}
}
// Render game items
void CircleLife::render()
{
	const int BUF_SIZE = 20;
	static char buffer[BUF_SIZE];
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();                      // add the pictures to the scene
	circle.draw();

	for (int i = 0; i < MAX_OBSTACLES_LR_NO; i++)
	{
		obstaclesLRList[i].draw();
		obstaclesUDList[i].draw();
	}
	for (int i = 0; i < MAX_OBSTACLES_NO; i++)
	{
		obstaclesFlyInList[i].draw();
	}
	// to check that MAX heart no is still greater than numofhits and draw out the corresponding number of hearts according to
	// numofhits < max heart no
	// so for example if number of hits = 1, the for loop will only draw 2 hearts since i < 3, and only 1 and 2 fulfils the condition
	if (numOfHits < MAX_HEART_NO)
	{
		for (int i = numOfHits; i < MAX_HEART_NO; i++)
		{
			heartList[i].draw();
		}
	}

	if (numOfHits >= MAX_HEART_NO)
	{
		const int BUF_SIZE = 100;
		static char buffer[BUF_SIZE];
		// prints out GAME OVER once num of hits becomes 3
		_snprintf_s(buffer, BUF_SIZE, "GAME OVER. Press Escape to exit game.");
		dxFont.print(buffer, GAME_WIDTH / 3, GAME_HEIGHT / 3);
		paused = true;
		if (input->isKeyDown(ESC_KEY))
		{
			exitGame();
		}
	}
	graphics->spriteEnd();                  // end drawing sprites
}
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset
void CircleLife::releaseAll()
{
	backgroundTexture.onLostDevice();
	circleTexture.onLostDevice();
	obstacleTexture.onLostDevice();
	heartTexture.onLostDevice();
	Game::releaseAll();
	return;
}
// The graphics device has been reset.
// Recreate all surfaces
void CircleLife::resetAll()
{
	backgroundTexture.onResetDevice();
	circleTexture.onResetDevice();
	obstacleTexture.onResetDevice();
	heartTexture.onResetDevice();
	Game::resetAll();
	return;
}

