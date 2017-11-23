#pragma once

#include "Sprite.hpp"

class SquareSprite : public Sprite
{
public:
	SquareSprite(int textureWidth, int textureHeight, std::string path, int frameAmount, int rowAmount);
	~SquareSprite();

	void Render(BYTE* screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha = false) override;

private:
	const int numFrames_, numRows_;
};
