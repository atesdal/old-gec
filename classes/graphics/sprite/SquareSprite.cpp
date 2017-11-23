#include "SquareSprite.hpp"

SquareSprite::SquareSprite(int textureWidth, int textureHeight, std::string path, int frameAmount, int rowAmount) :
	Sprite(textureWidth, textureHeight, path), numFrames_(frameAmount), numRows_(rowAmount)
{
}

SquareSprite::~SquareSprite()
{
}

void SquareSprite::Update()
{
}
