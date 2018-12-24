//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#include "obstacles.h"
#include <ctime>
//=============================================================================
// default constructor
//=============================================================================
Obstacles::Obstacles() : Entity()
{
	spriteData.width = obstaclesNS::WIDTH;           // size of Ship1
	spriteData.height = obstaclesNS::HEIGHT;
	spriteData.x = obstaclesNS::X;              // location on screen
	spriteData.y = obstaclesNS::Y;
	spriteData.rect.bottom = obstaclesNS::HEIGHT/2*spriteData.scale;
	spriteData.rect.right = obstaclesNS::WIDTH/2 * spriteData.scale;
	radius = obstaclesNS::WIDTH/2;
	mass = obstaclesNS::MASS;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = obstaclesNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesNS::END_FRAME;      // last frame of obstacle animation
	radius = obstaclesNS::COLLISION_RADIUS;
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;
	center = VECTOR2((spriteData.x + obstaclesNS::WIDTH / 2)* spriteData.scale, (spriteData.y + obstaclesNS::HEIGHT / 2)* spriteData.scale);
}


void Obstacles::updateRandomObstacles(float frameTime)
{
	Entity::update(frameTime);
	spriteData.y += frameTime * velocity.y;
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

