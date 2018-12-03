#include "obstacles.h"

//=============================================================================
// default constructor
//=============================================================================
Obstacles::Obstacles() : Entity()
{
	spriteData.width = obstaclesNS::WIDTH;           // size of Ship1
	spriteData.height = obstaclesNS::HEIGHT;
	spriteData.x = obstaclesNS::X;              // location on screen
	spriteData.y = obstaclesNS::Y;
	spriteData.rect.bottom = obstaclesNS::HEIGHT;
	spriteData.rect.right = obstaclesNS::WIDTH;
	radius = obstaclesNS::COLLISION_RADIUS;
	mass = obstaclesNS::MASS;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = obstaclesNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesNS::END_FRAME;      // last frame of obstacle animation
	radius = obstaclesNS::WIDTH;
	setCurrentFrame(startFrame);
	collisionType = entityNS::BOX;
}

void Obstacles::updateLeftRight(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move obstacle along X 

	
													// Bounce off walls
	if (spriteData.x > GAME_WIDTH - obstaclesNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - obstaclesNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
}


void Obstacles::updateTopDown(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;         // move obstacle along Y
													//spriteData.y += frameTime * velocity.y;         // move obstacle along Y


													// Bounce off walls
	if (spriteData.y > GAME_HEIGHT - obstaclesNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - obstaclesNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
}

void Obstacles::draw()
{
	Image::draw();              // draw circle
}

bool Obstacles::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	obstacle.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	obstacle.setFrames(obstaclesNS::START_FRAME, obstaclesNS::END_FRAME);
	obstacle.setCurrentFrame(obstaclesNS::START_FRAME);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}