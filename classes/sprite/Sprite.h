#pragma once

#include<HAPI_lib.h>
using namespace HAPISPACE;

class Sprite
{
public:
	Sprite(int textureWidth, int textureHeight);
	~Sprite();

	int Get_Width() const { return tWidth; }
	int Get_Height() const { return tHeight; }
	BYTE* Get_tPntr() { return tPntr; }

private:
	int tWidth, tHeight;
	BYTE *tPntr;
};

