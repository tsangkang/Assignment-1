#include "textureManager.h"
#define _TEXTUREMANAGER_H       // file is included in more than one place

// default constructor
TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;            // set true when successfully initialized
}


// destructor
TextureManager::~TextureManager()
{
	SAFE_RELEASE(texture);
}
