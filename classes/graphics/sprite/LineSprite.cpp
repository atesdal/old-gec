#include "LineSprite.hpp"

LineSprite::LineSprite(int textureWidth, int textureHeight, std::string path, int frameAmount) : Sprite(textureWidth, textureHeight, path), numFrames_(frameAmount)
{
}

LineSprite::~LineSprite()
{
}

void LineSprite::Update()
{
}
