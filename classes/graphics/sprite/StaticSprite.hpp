#pragma once
#include "Sprite.hpp"

class StaticSprite : public Sprite
{
public:
	StaticSprite(int textureWidth, int textureHeight, std::string path);
	~StaticSprite();

	void Update(BYTE* screenPtr, const Rectangle &dest, int posX, int posY) override;

private:
	//bool Alpha_Blit(BYTE *currSPtr, BYTE *currTPtr) override;
};
