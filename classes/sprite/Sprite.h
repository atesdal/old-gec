#pragma once

#include<HAPI_lib.h>
using namespace HAPISPACE;

class Sprite
{
public:
	//Creates sprite instance, initializes width, height and filepath
	Sprite(int textureWidth, int textureHeight, std::string path);
	//Destructor for sprites, called by Graphics destructor
	~Sprite();

	//Returns height of the sprite instance
	int Get_Height() const { return tHeight; }
	//Returns width of the sprite instance
	int Get_Width() const { return tWidth; }
	//Loads texture into memory using HAPI.LoadTexture
	bool Init_Texture();
	//Blits texture to screen using memcpy, not alpha compatible
	bool Fast_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY);
	//Blits texture to screen using double for loops, alpha compatible but slow
	bool Alpha_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY);

private:
	int tWidth, tHeight;
	std::string tPath;
	BYTE *tPntr;
};

