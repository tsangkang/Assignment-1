#ifndef _CIRCLE_H               // Prevent multiple definitions if this 
#define _CIRCLE_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace circleNS
{
	const int   WIDTH = 32;                // image width
	const int   HEIGHT = 32;               // image height
	const int   COLLISION_RADIUS = 120 / 2;   // for circular collision
	const int   X = GAME_WIDTH / 2 - circleNS::WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - circleNS::HEIGHT / 2;
	const float MASS = 500;         // mass
	const int   TEXTURE_COLS = 1;       // texture has 1 columns
	const int   START_FRAME = 0;        // starts at frame 1
	const int   END_FRAME = 0;          // no animation
	const int   COLS = 1;
}

class Circle : public Entity            // inherits from Entity class
{
private:
	Image circle;
public:
	// constructor
	Circle();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
};
#endif

