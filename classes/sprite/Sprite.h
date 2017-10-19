#pragma once

#include<HAPI_lib.h>
using namespace HAPISPACE;

class Sprite
{
public:
	Sprite(int textureWidth, int textureHeight, std::string path);
	~Sprite();

	int Get_Height() { return tHeight; }
	int Get_Width() { return tWidth; }
	bool Init_Texture();
	bool Draw_Texture(BYTE *screenPointer, int screenWidth) const;

private:
	int tWidth, tHeight;
	std::string tPath;
	BYTE *tPntr;
};

