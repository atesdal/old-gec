#pragma once

#include<HAPI_lib.h>
using namespace HAPISPACE;

#include "../rectangle/Rectangle.hpp"

class Sprite
{
public:
	//Creates sprite instance, initializes width, height and filepath
	Sprite(int textureWidth, int textureHeight, std::string path);
	//Destructor for sprites, called by Graphics destructor
	virtual ~Sprite();

	//Returns height of the sprite instance
	int Get_Height() const { return tHeight_; }
	//Returns width of the sprite instance
	int Get_Width() const { return tWidth_; }
	//Loads texture into memory using HAPI.LoadTexture
	bool Init_Texture();
	//Draws texture
	virtual void Render(BYTE* screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha = false) = 0;

protected:
	//Blits texture to screen using double for loops, alpha compatible but slow
	void Alpha_Blit(BYTE *currSPtr, BYTE *currTPtr);

	int tWidth_, tHeight_;
	std::string tPath_;
	BYTE *tPntr_;
	Rectangle frameRect_;
};
