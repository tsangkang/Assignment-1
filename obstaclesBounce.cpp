//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#include "obstaclesBounce.h"
#include <ctime>
//=============================================================================
// default constructor
//=============================================================================
ObstaclesBounce::ObstaclesBounce() : Entity()
{
	spriteData.width = obstaclesBounceNS::WIDTH;           // size of Ship1
	spriteData.height = obstaclesBounceNS::HEIGHT;
	spriteData.x = obstaclesBounceNS::X;              // location on screen
	spriteData.y = obstaclesBounceNS::Y;
	spriteData.rect.bottom = obstaclesBounceNS::HEIGHT / 2 * spriteData.scale;
	spriteData.rect.right = obstaclesBounceNS::WIDTH / 2 * spriteData.scale;
	radius = obstaclesBounceNS::WIDTH / 2;
	mass = obstaclesBounceNS::MASS;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = obstaclesBounceNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesBounceNS::END_FRAME;      // last frame of obstacle animation
	radius = obstaclesBounceNS::COLLISION_RADIUS;
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;
	center = VECTOR2((spriteData.x + obstaclesBounceNS::WIDTH / 2)* spriteData.scale, (spriteData.y + obstaclesBounceNS::HEIGHT / 2)* spriteData.scale);
}

void ObstaclesBounce::updateLeftRight(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move obstacle along X 


													// Bounce off walls
	if (spriteData.x > GAME_WIDTH - obstaclesBounceNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - obstaclesBounceNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
}

void ObstaclesBounce::updateUpDown(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;         // move obstacle along Y
													//spriteData.y += frameTime * velocity.y;         // move obstacle along Y


													// Bounce off walls
	if (spriteData.y > GAME_HEIGHT - obstaclesBounceNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - obstaclesBounceNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
}


void ObstaclesBounce::updateRandomObstacles(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;
}

void ObstaclesBounce::draw()
{
	Image::draw();              // draw circle
}

bool ObstaclesBounce::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	obstacle.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	obstacle.setFrames(obstaclesBounceNS::START_FRAME, obstaclesBounceNS::END_FRAME);
	obstacle.setCurrentFrame(obstaclesBounceNS::START_FRAME);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

