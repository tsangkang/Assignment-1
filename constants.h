//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)

#pragma once
#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>



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
#define TRANSCOLOR  SETCOLOR_ARGB(255,255,0,255)

//Constants
// graphic images
const char background_IMAGE[] = "pictures\\background3.png";  // photo source courtesy of pexel
const char CIRCLE_IMAGE[] = "pictures\\circle.png";   // player character
const char OBSTACLE1_IMAGE[] = "pictures\\obstacle1.png"; // obstacle 1
const char OBSTACLE2_IMAGE[] = "pictures\\obstacle1.png"; // obstacle 2
const char OBSTACLE3_IMAGE[] = "pictures\\obstacle1.png"; // obstacle 3
const char OBSTACLE4_IMAGE[] = "pictures\\obstacle1.png"; // obstacle 4
const char OBSTACLE5_IMAGE[] = "pictures\\obstacle2.png"; // obstacle 5
const char HEALTHBARRED_IMAGE[] = "pictures\\healthBarRed.png";
const char HEALTHBARBACKGROUND_IMAGE[] = "pictures\\healthBarBackground.png"; //healthbar

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


const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float CIRCLE_SPEED = 350.0f;                // pixels per second
const float CIRCLE_SCALE = 1.5f;                  // starting circle scale

const UCHAR CIRCLE_RIGHT_KEY = VK_RIGHT;
const UCHAR CIRCLE_LEFT_KEY = VK_LEFT;
const UCHAR CIRCLE_DOWN_KEY = VK_DOWN;
const UCHAR CIRCLE_UP_KEY = VK_UP;


const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
#endif