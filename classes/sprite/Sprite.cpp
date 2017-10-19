#include "Sprite.h"

Sprite::Sprite(int textureWidth, int textureHeight)
{
	tWidth = textureWidth;
	tHeight = textureHeight;
	tPntr =  nullptr;
}

Sprite::~Sprite()
{
	delete tPntr;
}


