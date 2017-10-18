#include "Sprite.h"

Sprite::Sprite(int textureWidth, int textureHeight, const std::string filePath)
{
	tWidth = textureWidth;
	tHeight = textureHeight;
	path = filePath;
}

Sprite::~Sprite()
{

}


