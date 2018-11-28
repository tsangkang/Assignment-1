#include "circle.h"

//=============================================================================
// default constructor
//=============================================================================
Circle::Circle() : Entity()
{
	spriteData.width = circleNS::WIDTH;
	spriteData.height = circleNS::HEIGHT;
	spriteData.x = circleNS::X;              // location on screen
	spriteData.y = circleNS::Y;
	spriteData.rect.bottom = circleNS::HEIGHT;
	spriteData.rect.right = circleNS::WIDTH;
	radius = circleNS::COLLISION_RADIUS;
	mass = circleNS::MASS;
	startFrame = circleNS::START_FRAME;    // first frame of obstacle animation
	endFrame = circleNS::END_FRAME;      // last frame of obstacle animation
	setCurrentFrame(startFrame);
}