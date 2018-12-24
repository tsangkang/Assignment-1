//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#include "obstaclesUD.h"
#include <ctime>
//=============================================================================
// default constructor
//=============================================================================
ObstaclesUD::ObstaclesUD() : Entity()
{
	spriteData.width = obstaclesUDNS::WIDTH;           // size of Ship1
	spriteData.height = obstaclesUDNS::HEIGHT;
	spriteData.x = obstaclesUDNS::X;              // location on screen
	spriteData.y = obstaclesUDNS::Y;
	spriteData.rect.bottom = obstaclesUDNS::HEIGHT / 2 * spriteData.scale;
	spriteData.rect.right = obstaclesUDNS::WIDTH / 2 * spriteData.scale;
	radius = obstaclesUDNS::WIDTH / 2;
	mass = obstaclesUDNS::MASS;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = obstaclesUDNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesUDNS::END_FRAME;      // last frame of obstacle animation
	radius = obstaclesUDNS::COLLISION_RADIUS;
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;
	center = VECTOR2((spriteData.x + obstaclesUDNS::WIDTH / 2)* spriteData.scale, (spriteData.y + obstaclesUDNS::HEIGHT / 2)* spriteData.scale);
}

void ObstaclesUD::updateUpDown(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;         // move obstacle along Y
													//spriteData.y += frameTime * velocity.y;         // move obstacle along Y


													// Bounce off walls
	if (spriteData.y > GAME_HEIGHT - obstaclesUDNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - obstaclesUDNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
}
void ObstaclesUD::updateRandomObstacles(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;
}

void ObstaclesUD::draw()
{
	Image::draw();              // draw circle
}

bool ObstaclesUD::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	obstacle.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	obstacle.setFrames(obstaclesUDNS::START_FRAME, obstaclesUDNS::END_FRAME);
	obstacle.setCurrentFrame(obstaclesUDNS::START_FRAME);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

