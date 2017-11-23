#pragma once
#include "Sprite.hpp"

class LineSprite : public Sprite
{
public:
	LineSprite(int textureWidth, int textureHeight, std::string path, int frameAmount);
	~LineSprite();

	void Update();

private:
	const int numFrames_;
};
