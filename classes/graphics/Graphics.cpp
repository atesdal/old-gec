#include "Graphics.h"
#include <algorithm>

Graphics::Graphics(int windowWidth, int windowHeight, BYTE *screenPointer) :
	wWidth(windowWidth), wHeight(windowHeight), startOfScreen(screenPointer),
	screenRect(windowWidth, windowHeight)
{
	//Enforce no nullpointer, no negative dimensions
}

Graphics::~Graphics()
{
	for (auto p : spriteMap) {
		delete p.second;
	}
}

void Graphics::Clear_Screen(int grayScale)
{
	if (grayScale < 0 || grayScale > 255) {
		std::cout << "Clear_Screen(grayScale) out of bounds, check values!" << std::endl;
	}
	memset(startOfScreen, std::max(0, std::min(255, grayScale)), (wWidth * wHeight * 4));
}

void Graphics::Clear_Screen(HAPI_TColour screenColour)
{
	BYTE *scrPntr = startOfScreen;
	HAPI_TColour col = screenColour;
	for (int i{ 0 }; i < (wWidth * wHeight); i++) {
		memcpy(scrPntr, &col, sizeof(HAPI_TColour));
		scrPntr += sizeof(HAPI_TColour);
	}
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale)
{
	if (shapeWidth > wWidth || shapeHeight > wHeight) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale))", "Error");
		return false;
	}

	BYTE *scrPntr = startOfScreen;

	int endIncrement = wWidth * 4;
	for (int h{ 0 }; h < shapeHeight; h++) {
		memset(scrPntr, grayScale, (sizeof(HAPI_TColour) * shapeWidth));
		scrPntr += endIncrement;
	}
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale)
{
	if ((shapeWidth + posX) > wWidth || posX < 0) { 
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale))", "Error");
		return false; 
	}
	else if ((shapeHeight + posY) > wHeight || posY < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale))", "Error");
		return false; } // and Y-direction

	int endIncrement = wWidth * 4;
	int startByte = (posX + (posY * wWidth)) * 4;

	BYTE *scrPntr = startOfScreen;
	scrPntr += startByte; //Sets screen pointer to original writing position

	for (int h{ startByte }; h < (wWidth * shapeHeight * 4) + startByte; h += endIncrement) {
		memset(scrPntr, grayScale, (sizeof(HAPI_TColour) * shapeWidth));
		scrPntr += endIncrement;
	}
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour)
{
	if (shapeWidth > wWidth || shapeHeight > wHeight) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour))", "Error");
		return false;
	}

	BYTE *scrPntr = startOfScreen;
	int endIncrement = (wWidth - shapeWidth) * 4;

	for (int h{ 0 }; h < shapeHeight; h++) {
		for (int w{ 0 }; w < shapeWidth; w++) {
			memcpy(scrPntr, &shapeColour, sizeof(HAPI_TColour));
			scrPntr += sizeof(HAPI_TColour);
		}
		scrPntr += endIncrement;
	}
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour)
{
	if ((shapeWidth + posX) > wWidth || posX < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour))", "Error");
		return false;
	} 
	else if ((shapeHeight + posY) > wHeight || posY < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour))", "Error");
		return false;
	}

	int endIncrement = (wWidth - shapeWidth) * 4;
	int startByte = (posX + (posY * wWidth)) * 4;

	BYTE *scrPntr = startOfScreen;
	scrPntr += startByte; //Sets screen pointer to original writing position

	for (int h{ startByte }; h < shapeHeight + startByte; h++) {
		for (int w{ 0 }; w < shapeWidth; w++) {
			memcpy(scrPntr, &shapeColour, sizeof(HAPI_TColour));
			scrPntr += sizeof(HAPI_TColour);
		}
		scrPntr += endIncrement;
	}
	return true;
}

bool Graphics::Create_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height)
{
	if (spriteMap.find(uniqueName) == spriteMap.end()) {
		Sprite *a = new Sprite(width, height, fileName);
		if (!a->Init_Texture()) {
			delete a;
			return false;
		}
		spriteMap[uniqueName] = a;
		std::cout << spriteMap.at(uniqueName)->Get_Height();
		return true;
	}
	return false;
}

bool Graphics::Create_Anim_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height, int fWidth, int fHeight, int numFrames, int animRow)
{
	if (spriteMap.find(uniqueName) == spriteMap.end()) {
		Sprite *a = new Sprite(width, height, fileName, fWidth, fHeight, numFrames, animRow);
		if (!a->Init_Texture()) {
			delete a;
			return false;
		}
		spriteMap[uniqueName] = a;
		std::cout << spriteMap.at(uniqueName)->Get_Height();
		return true;
	}
	return false;
}

bool Graphics::Draw_Sprite(const std::string &spriteName, int posX, int posY) const
{
	if (spriteMap.find(spriteName) == spriteMap.end()) {
		return false;
	}
	spriteMap.at(spriteName)->Alpha_Blit(startOfScreen, posX, posY, screenRect);
	return true;
}
