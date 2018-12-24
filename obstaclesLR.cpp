//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#include "obstaclesLR.h"
#include <ctime>
//=============================================================================
// default constructor
//=============================================================================
ObstaclesLR::ObstaclesLR() : Entity()
{
	spriteData.width = obstaclesLRNS::WIDTH;           // size of Ship1
	spriteData.height = obstaclesLRNS::HEIGHT;
	spriteData.x = obstaclesLRNS::X;              // location on screen
	spriteData.y = obstaclesLRNS::Y;
	spriteData.rect.bottom = obstaclesLRNS::HEIGHT / 2 * spriteData.scale;
	spriteData.rect.right = obstaclesLRNS::WIDTH / 2 * spriteData.scale;
	radius = obstaclesLRNS::WIDTH / 2;
	mass = obstaclesLRNS::MASS;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = obstaclesLRNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesLRNS::END_FRAME;      // last frame of obstacle animation
	radius = obstaclesLRNS::COLLISION_RADIUS;
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;
	center = VECTOR2((spriteData.x + obstaclesLRNS::WIDTH / 2)* spriteData.scale, (spriteData.y + obstaclesLRNS::HEIGHT / 2)* spriteData.scale);
}

void ObstaclesLR::updateLeftRight(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move obstacle along X 


													// Bounce off walls
	if (spriteData.x > GAME_WIDTH - obstaclesLRNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - obstaclesLRNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
}




void ObstaclesLR::updateRandomObstacles(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;
}

void ObstaclesLR::draw()
{
	Image::draw();              // draw circle
}

bool ObstaclesLR::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	obstacle.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	obstacle.setFrames(obstaclesLRNS::START_FRAME, obstaclesLRNS::END_FRAME);
	obstacle.setCurrentFrame(obstaclesLRNS::START_FRAME);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

