#pragma once
#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

// Useful macros

// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)


//Constants
// graphic images
const char NEBULA_IMAGE[] = "pictures\\background1.png";  // photo source NASA/courtesy of nasaimages.org 
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet
const char SHIP_IMAGE[] = "pictures\\ship4.png";   // spaceship

												  // window
const char CLASS_NAME[] = "CircleLife";
const char GAME_TITLE[] = "Circle of Life";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT  GAME_WIDTH = 1366;              // width of game in pixels
const UINT  GAME_HEIGHT = 768;              // height of game in pixels

											// key mappings
											// In this game simple constants are used for key mappings. If variables were used
											// it would be possible to save and restore key mappings from a data file.
											//const byte ESC_KEY = VK_ESCAPE;         // escape key
											//const byte SPACE_BAR = VK_SPACE;

											// Game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;					// the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;					// the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;		// minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;	// maximum time used in calculations

const int SHIP_WIDTH = 32;				 // ship width
const int SHIP_HEIGHT = 32;				 // ship height
const int SHIP_COLS = 1;				 // ship columns
const int  SHIP_START_FRAME = 0;         // starting frame of ship animation
const int  SHIP_END_FRAME = 0;           // last frame of ship animation




const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float SHIP_SPEED = 100.0f;                // pixels per second
const float SHIP_SCALE = 1.5f;                  // starting ship scale

const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;
const UCHAR SHIP_LEFT_KEY = VK_LEFT;
const UCHAR SHIP_DOWN_KEY = VK_DOWN;
const UCHAR SHIP_UP_KEY = VK_UP;

#endif