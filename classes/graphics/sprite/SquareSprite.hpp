#pragma once

#include "Sprite.hpp"

class SquareSprite : public Sprite
{
public:
	SquareSprite(int textureWidth, int textureHeight, std::string path, int frameAmount, int rowAmount, int numLoops = 0);
	~SquareSprite();

	void Render(BYTE* screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha = false) override;
	//Sets amount of times animation will loop, 0 = infinite
	void Set_Loop(int amount) override;

private:
	const int numFrames_, numRows_;
	int frameNum_, numLoops_, loopCounter_;
};
