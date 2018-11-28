#include "obstacles.h"

//=============================================================================
// default constructor
//=============================================================================
Obstacles::Obstacles() : Entity()
{
	spriteData.x = obstaclesNS::X;              // location on screen
	spriteData.y = obstaclesNS::Y;
	radius = obstaclesNS::COLLISION_RADIUS;
	mass = obstaclesNS::MASS;
	startFrame = obstaclesNS::START_FRAME;    // first frame of obstacle animation
	endFrame = obstaclesNS::END_FRAME;      // last frame of obstacle animation
	setCurrentFrame(startFrame);
}