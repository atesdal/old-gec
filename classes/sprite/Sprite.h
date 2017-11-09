#pragma once

#include<HAPI_lib.h>
using namespace HAPISPACE;

#include "../rectangle/Rectangle.h"

class Sprite
{
public:
	//Creates sprite instance, initializes width, height and filepath
	Sprite(int textureWidth, int textureHeight, std::string path);
	//Creates animated sprite instance, initializes width, height and filepath
	Sprite(int textureWidth, int textureHeight, std::string path, int frameWidth, int frameHeight, int numOfFrames, int animRow);
	//Destructor for sprites, called by Graphics destructor
	~Sprite();

	//Returns height of the sprite instance
	int Get_Height() const { return tHeight; }
	//Returns width of the sprite instance
	int Get_Width() const { return tWidth; }
	//Loads texture into memory using HAPI.LoadTexture
	bool Init_Texture();
	//Blits texture to screen using memcpy, not alpha compatible
	bool Fast_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest);
	//Blits texture to screen using double for loops, alpha compatible but slow
	bool Alpha_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest);
	//Changes the current animation row
	bool Change_Anim(int newRow);

private:
	int tWidth, tHeight, fNum, numFrames, rowNum;
	std::string tPath;
	BYTE *tPntr;
	Rectangle frameRect;
};
