//Work of Benedict Yee JianHui (S10173071G) and Tsang Hong Kang (S10172695F)


#ifndef _GAME_H			// prevent multiple definition if this
#define _GAME_H			// .. file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"
#include "TextDX.h"

// Class declaration to be inserted here
namespace gameNS
{
	const char FONT[] = "Courier New";  // font
	const int POINT_SIZE = 30;          // point size
	const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255, 255, 15, 15);    // white
}

class Game
{
protected:
	// Common game properties
	Graphics *graphics;			// pointer to Graphics
	Input *input;				// pointer to Input
	HWND hwnd;					// window handle
	HRESULT hr;					// standard return type
	LARGE_INTEGER timeStart;	// Performance Counter start value
	LARGE_INTEGER timeEnd;		// Performance Counter end value
	LARGE_INTEGER timerFreq;	// Perofrmance Counter frequency
	float frameTime;			// time required for last frame
	float fps;					// frames per second
	DWORD sleepTime;			// number of milli-seconds to sleep between frames
	bool paused;				// true if game is paused
	TextDX  dxFont;             // DirectX font for fps
	bool initialized;
public:
	Game();
	virtual ~Game();

	// Member functions

	// Window message handler
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Initialize the game
	// Pre" hwnd is handle to window
	virtual void initialize(HWND hwnd);
	// Call run repeatedly by the main message loop in WinMain
	virtual void run(HWND);
	// Call when the graphics device was lost.
	// Release all reserved video memory so graphics device may be reset
	virtual void releaseAll();
	// Recreate all surfaces and reset all entities
	virtual void resetAll();
	// Delete all reserved memory
	virtual void deleteAll();
	// Render game items
	virtual void renderGame();
	virtual void render() = 0;
	// Handle lost graphics device
	virtual void handleLostGraphicsDevice();
	// Return pointer to Graphics
	Graphics* getGraphics() { return graphics; }
	// Return pointer to Input
	Input* getInput() { return input; }
	// Exit the game
	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	// Pure virtual function declarations
	// These functions MUST be written in any class that inherits from Game

	// Update game items
	virtual void update() = 0;
	// Perform AI calculations
	virtual void ai() = 0;

	// Check for collisions
	virtual void collisions() = 0;
	// Render graphics
	// Call graphics->spriteBegin();
	//		draw sprites
	// Call graphics->spriteEnd();
	//		draw non-sprites
};

#endif