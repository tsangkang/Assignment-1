// GPP
#ifndef _HEART_H                 // Prevent multiple definitions if this 
#define _HEART_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{

	const int WIDTH = 136;                   // image width
	const int HEIGHT = 120;                  // image height


	const int X = 0;   // location on screen
	const int Y = 0;
	const float ROTATION_RATE = (float)PI / 4; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass

	// Remember to change
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   HEART_START_FRAME = 0;      // starts at frame 0
	const int   HEART_END_FRAME = 0;        // no animation
	const float MAX_HEART_SCALE = 0.3;
	const int   COLLISION_RADIUS = WIDTH / 2;   // for circular collision
}

// inherits from Entity class
class Heart : public Entity
{
private:

public:
	// constructor
	Heart();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

};
#endif