#include "Graphics.h"

Graphics::Graphics(int windowWidth, int windowHeight, BYTE *screenPointer)
{
	wWidth = windowWidth;
	wHeight = windowHeight;
	scrPntr = screenPointer;
	startOfScreen = screenPointer;
}

Graphics::~Graphics()
{
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale)
{
	if (shapeWidth > wWidth || shapeHeight > wHeight) { return false; }
	
	int endOfLineInc = wWidth * 4;
	for (int h{ 0 }; h < shapeHeight; h++) {
		memset(scrPntr, grayScale, (sizeof(BYTE) * 4 * shapeWidth));
		scrPntr += endOfLineInc;
	}
	scrPntr = startOfScreen;
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY)
{
	return false;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int R, int G, int B)
{
	return false;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour)
{
	return false;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int R, int G, int B)
{
	return false;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour)
{
	return false;
}

