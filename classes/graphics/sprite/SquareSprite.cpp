#include "SquareSprite.hpp"

SquareSprite::SquareSprite(int textureWidth, int textureHeight, std::string path, int frameAmount, int rowAmount, int numLoops) :
	Sprite(textureWidth, textureHeight, path), frameNum_(0), numFrames_(frameAmount), numRows_(rowAmount), numLoops_(numLoops)
{
}

SquareSprite::~SquareSprite()
{
	delete[] tPntr_;
}

void SquareSprite::Render(BYTE* screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha)
{
}

void SquareSprite::Set_Loop(int amount)
{
}
