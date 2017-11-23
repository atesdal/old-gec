#include "LineSprite.hpp"

LineSprite::LineSprite(int textureWidth, int textureHeight, std::string path, int frameAmount) : Sprite(textureWidth, textureHeight, path), numFrames_(frameAmount)
{
}

LineSprite::~LineSprite()
{
	delete[] tPntr_;
}

void LineSprite::Render(BYTE* screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha)
{
}
