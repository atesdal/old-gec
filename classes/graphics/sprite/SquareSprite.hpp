#pragma once

#include "Sprite.hpp"

class SquareSprite : public Sprite
{
public:
	SquareSprite(int textureWidth, int textureHeight, std::string path, int framesPerRow, int rowAmount, DWORD frameTimeMS, int numLoops = 0);
	~SquareSprite();

	void Render(BYTE *screenPtr, const Util::Rectangle *dest, int posX, int posY, bool forceNonAlpha = false) override;
	//Resets loop counter
	void Reset_Loop() override;
	//Sets amount of times animation will loop, 0 = infinite
	void Set_Loop(int amount) override;

private:
	const int numFrames_, numRows_;
	int frameNum_, rowNum_, numLoops_, loopCounter_;
	DWORD lastUpdate_;
	const DWORD frameDelay_;
};
