#pragma once

#include "Sprite.hpp"

class LineSprite : public Sprite
{
public:
	LineSprite(int textureWidth, int textureHeight, std::string path, int frameAmount);
	~LineSprite();

	void Render(BYTE* screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha = false) override;

private:
	const int numFrames_;
};
