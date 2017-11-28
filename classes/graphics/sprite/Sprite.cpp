#include "Sprite.hpp"

Sprite::Sprite(int textureWidth, int textureHeight, std::string path) :
	tWidth_(textureWidth), tHeight_(textureHeight), tPath_(path), tPntr_(nullptr), frameRect_(textureWidth, textureHeight)
{

}

Sprite::~Sprite()
{

}

bool Sprite::Init_Texture()
{
	if (!HAPI.LoadTexture(tPath_, &tPntr_, tWidth_, tHeight_)) {
		HAPI.UserMessage("Error(Init_Texture)", "Error");
		return false;
	}
	return true;
}

void Sprite::Set_Loop(int amount)
{
	HAPI.UserMessage("Sprites of this type cannot loop.", "Error");
}

void Sprite::Reset_Loop()
{
	HAPI.UserMessage("Sprites of this type cannot loop.", "Error");
}

void Sprite::Alpha_Blit(BYTE *currSPtr, BYTE *currTPtr)
{
	BYTE alpha = currTPtr[3];
	currSPtr[0] += ((alpha * (currTPtr[2] - currSPtr[0])) >> 8);
	currSPtr[1] += ((alpha * (currTPtr[1] - currSPtr[1])) >> 8);
	currSPtr[2] += ((alpha * (currTPtr[0] - currSPtr[2])) >> 8);
}
