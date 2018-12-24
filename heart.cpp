#include "heart.h"

//===========================
//default constructor
//===========================

Heart::Heart() : Entity()
{
	spriteData.x = heartNS::X;
	spriteData.y = heartNS::Y;
	spriteData.scale = heartNS::MAX_HEART_SCALE;
	radius = heartNS::COLLISION_RADIUS;
	startFrame = heartNS::HEART_START_FRAME;
	endFrame = heartNS::HEART_END_FRAME;
	setCurrentFrame(startFrame);
}


// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Heart::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{

	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Heart::draw()
{

	//spriteData.scale = 0.5;

	Image::draw();              // draw ship


}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Heart::update(float frameTime)
{
	Entity::update(frameTime);
}
