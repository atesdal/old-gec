#pragma once
#include "Sprite.hpp"

class SquareSprite : public Sprite
{
public:
	SquareSprite(int textureWidth, int textureHeight, std::string path, int frameAmount, int rowAmount);
	~SquareSprite();

	void Update();

private:
	const int numFrames_, numRows_;
};
