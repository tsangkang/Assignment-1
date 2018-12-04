#pragma once
#ifndef _GRAPHICS_H             // prevent multiple definitions if this 
#define _GRAPHICS_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"

// DirectX pointer types
#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_3D       LPDIRECT3D9
#define LP_SPRITE   LPD3DXSPRITE
#define VECTOR2     D3DXVECTOR2
#define LP_DXFONT	LPD3DXFONT

// Color defines
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
	// Some common colors
	// ARGB numbers range from 0 through 255
	// A = Alpha channel (transparency where 255 is opaque)
	// R = Red, G = Green, B = Blue
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);  // use to specify drawing with colorFilter
	const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);  // AND with color to get 25% alpha
	const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);  // AND with color to get 50% alpha
	const COLOR_ARGB BACK_COLOR = NAVY;                         // background color of game

	enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}


struct SpriteData
{
	int         width;      // width of sprite in pixels
	int         height;     // height of sprite in pixels
	float       x;          // screen location (top left corner of sprite)
	float       y;
	float       scale;      // <1 smaller, >1 bigger
	float       angle;      // rotation angle in radians
	RECT        rect;       // used to select an image from a larger texture
	LP_TEXTURE  texture;    // pointer to texture
	bool        flipHorizontal; // true to flip sprite horizontally (mirror)
	bool        flipVertical;   // true to flip sprite vertically
};

class Graphics
{
private:
	// DirectX pointers and stuff
	LP_3D       direct3d;
	LP_3DDEVICE device3d;
	LP_SPRITE   sprite;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

	// other variables
	HRESULT     result;         // standard Windows return codes
	HWND        hwnd;
	bool        fullscreen;
	int         width;
	int         height;
	COLOR_ARGB	backColor;		// background color

								// (For internal engine use only. No user serviceable parts inside.)
								// Initialize D3D presentation parameters
	void    initD3Dpp();



public:
	// Constructor
	Graphics();
	// Destructor
	virtual ~Graphics();
	// Releases direct3d and device3d.
	void    releaseAll();

	// Initialize DirectX graphics
	// Throws GameError on error
	// Pre: hw = handle to window
	//      width = width in pixels
	//      height = height in pixels
	//      fullscreen = true for full screen, false for window
	void    initialize(HWND hw, int width, int height, bool fullscreen);

	// Display the offscreen backbuffer to the screen.
	HRESULT showBackbuffer();
	// Set colour used to clear screen
	void	setBackColor(COLOR_ARGB c);
	// get functions
	// Return direct3d
	LP_3D get3D()
	{
		return direct3d;
	}
	// Return device3d
	LP_3DDEVICE get3Ddevice()
	{
		return device3d;
	}
	// Return handle to deice context (window)
	HDC getDC()
	{
		return GetDC(hwnd);
	}
	// Reset the graphics device
	HRESULT reset();
	// Test for lost device
	HRESULT getDeviceState();

	// Clear backbuffer and BeginScene()
	HRESULT beginScene()
	{
		result = E_FAIL;
		if (device3d == NULL)
			return result;
		// clear backbuffer to backColor
		device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
		result = device3d->BeginScene();		// begin scene for drawing
		return result;
	}
	// EndScene()
	HRESULT endScene()
	{
		result = E_FAIL;
		if (device3d)
			result = device3d->EndScene();
		return result;
	}


	void Graphics::drawSprite(const SpriteData &spriteData, COLOR_ARGB color = graphicsNS::WHITE);
	// Load the texture into default D3D memory (normal texture use)
	HRESULT loadTexture(const char * filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture);
	// Draw the sprite described in SpriteData structure.


	//=============================================================================
	// Sprite Begin
	//=============================================================================

	LP_SPRITE   getSprite() { return sprite; }
	void spriteBegin()
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	//=============================================================================
	// Sprite End
	//=============================================================================
	void spriteEnd()
	{
		sprite->End();
	}

	// Return length of vector v as a float.
	static float    Vector2Length(const VECTOR2 *v) { return D3DXVec2Length(v); }

	// Return Dot product of unit vector v1 and vector v2.
	static float    Vector2Dot(const VECTOR2 *v1, const VECTOR2 *v2)
	{
		return D3DXVec2Dot(v1, v2);
	}

	// Normalize vector v
	static void     Vector2Normalize(VECTOR2 *v) { D3DXVec2Normalize(v, v); }
};


#endif