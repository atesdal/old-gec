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

void Graphics::Clear_Screen(int grayScale)
{
	memset(scrPntr, grayScale, (wWidth * wHeight * 4));
}

void Graphics::Clear_Screen(int r, int g, int b)
{
	HAPI_TColour col = HAPI_TColour(r, g, b, 0);
	for (int i{ 0 }; i < (wWidth * wHeight); i++) {
		memcpy(scrPntr, &col, sizeof(HAPI_TColour));
		scrPntr += sizeof(HAPI_TColour);
	}
	scrPntr = startOfScreen;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale)
{
	if (shapeWidth > wWidth || shapeHeight > wHeight) { return false; }
	
	int endIncrement = wWidth * 4;
	for (int h{ 0 }; h < shapeHeight; h++) {
		memset(scrPntr, grayScale, (sizeof(HAPI_TColour) * shapeWidth));
		scrPntr += endIncrement;
	}
	scrPntr = startOfScreen;
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale)
{
	if ((shapeWidth + posX) > wWidth || posX < 0) { return false; } //Checks that pixels can be drawn in X-direction
	else if ((shapeHeight + posY) > wHeight || posY < 0) { return false; } // and Y-direction

	int endIncrement = wWidth * 4;
	int startByte = (posX + (posY * wWidth)) * 4;

	scrPntr += startByte; //Sets screen pointer to original writing position

	for (int h{ startByte }; h < (wWidth * shapeHeight * 4) + startByte; h += endIncrement) {
		memset(scrPntr, grayScale, (sizeof(HAPI_TColour) * shapeWidth));
		scrPntr += endIncrement;
	}
	scrPntr = startOfScreen;
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour)
{
	if (shapeWidth > wWidth || shapeHeight > wHeight) { return false; }

	int endIncrement = (wWidth - (shapeWidth - 1)) * 4;

	for (int h{ 1 }; h <= (shapeHeight * shapeWidth); h++) {
		if (h % shapeWidth == 0) {
			memcpy(scrPntr, &shapeColour, sizeof(HAPI_TColour));
			scrPntr += endIncrement;
		}
		else {
			memcpy(scrPntr, &shapeColour, sizeof(HAPI_TColour));
			scrPntr += sizeof(HAPI_TColour);
		}
	}
	scrPntr = startOfScreen;
	return true;
}


bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour)
{
	if ((shapeWidth + posX) > wWidth || posX < 0) { return false; } //Checks that pixels can be drawn in X-direction
	else if ((shapeHeight + posY) > wHeight || posY < 0) { return false; } // and Y-direction

	int endIncrement = (wWidth - (shapeWidth - 1)) * 4;

	int startByte = (posX + (posY * wWidth)) * 4;

	scrPntr += startByte; //Sets screen pointer to original writing position

	for (int h{ startByte }; h < (shapeHeight * shapeWidth) + startByte; h++) {
		memcpy(scrPntr, &shapeColour, sizeof(HAPI_TColour));
		if ((h - startByte + 1) % shapeWidth == 0) {
			scrPntr += endIncrement;
		}
		else {
			scrPntr += sizeof(HAPI_TColour);
		}
	}
	scrPntr = startOfScreen;
	return true;
}