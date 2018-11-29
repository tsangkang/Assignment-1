#include "obstacles.h"

//=============================================================================
// default constructor
//=============================================================================
Obstacles::Obstacles() : Entity()
{
	spriteData.x = obstaclesNS::X;              // location on screen
	spriteData.y = obstaclesNS::Y;
	spriteData.rect.bottom = obstaclesNS::HEIGHT;
	spriteData.rect.right = obstaclesNS::WIDTH;
	radius = obstaclesNS::COLLISION_RADIUS;
	mass = obstaclesNS::MASS;
	startFrame = obstaclesNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesNS::END_FRAME;      // last frame of obstacle animation
	setCurrentFrame(startFrame);
	collisionType = entityNS::BOX;
}