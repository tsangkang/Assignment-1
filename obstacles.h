//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#ifndef _OBSTACLES_H               // Prevent multiple definitions if this 
#define _OSBTACLES_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace obstaclesNS
{
	const int   WIDTH = 128;                // image width
	const int   HEIGHT = 128;               // image height
	const int   COLLISION_RADIUS = 120/2;   // for circular collision
	const float SPEED = 200;                // pixels per second
	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float MASS = 500;         // mass
	const int   TEXTURE_COLS = 1;       // texture has 2 columns
	const int   START_FRAME = 0;        // starts at frame 1
	const int   END_FRAME = 0;          // no animation
}

class Obstacles : public Entity            // inherits from Entity class
{
private:
	Image obstacle;
	bool isCollided = false;

public:
	// constructor
	Obstacles();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void updateLeftRight(float frameTime);
	void updateTopDown(float frameTime);
	void updateRandomObstacles(float frameTime);
};
#endif

