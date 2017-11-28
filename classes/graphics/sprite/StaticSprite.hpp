#pragma once

#include "Sprite.hpp"

class StaticSprite : public Sprite
{
public:
	StaticSprite(int textureWidth, int textureHeight, std::string path);
	~StaticSprite();

	void Render(BYTE *screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha = false) override;
};
