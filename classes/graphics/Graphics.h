#pragma once

#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <unordered_map>
#include "../sprite/Sprite.h"

class Graphics
{
public:
	Graphics(int windowWidth, int windowHeight, BYTE *screenPointer);
	~Graphics();

	void Clear_Screen(int grayScale);
	void Clear_Screen(int r, int g, int b);
	bool Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale);
	bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale);
	bool Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour);
	bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour);

	bool Create_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height);
protected:

private:
	int wWidth, wHeight;
	BYTE *startOfScreen;
	std::unordered_map<std::string, Sprite*> spriteMap;
};