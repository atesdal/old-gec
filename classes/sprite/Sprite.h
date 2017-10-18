#pragma once

#include<HAPI_lib.h>
using namespace HAPISPACE;

class Sprite
{
public:
	Sprite(int textureWidth, int textureHeight, const std::string filePath);
	~Sprite();

private:
	int tWidth, tHeight;
	std::string path;
};

