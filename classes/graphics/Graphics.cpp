#include "Graphics.hpp"
#include "sprite\Sprite.hpp"
#include <algorithm>
#include <cassert>

Graphics::Graphics(int windowWidth, int windowHeight, BYTE *screenPointer) :
	wWidth_(windowWidth), wHeight_(windowHeight), startOfScreen_(screenPointer),
	screenRect_(windowWidth, windowHeight)
{
	assert(screenPointer);
	//Enforce no nullpointer, no negative dimensions
}

Graphics::~Graphics()
{
	for (auto p : spriteMap_) {
		delete p.second;
	}
}

void Graphics::Clear_Screen(int grayScale)
{
	if (grayScale < 0 || grayScale > 255) {
		std::cout << "Clear_Screen(grayScale) out of bounds, check values!" << std::endl;
	}
	memset(startOfScreen_, std::max(0, std::min(255, grayScale)), (wWidth_ * wHeight_ * 4));
}

void Graphics::Clear_Screen(HAPI_TColour screenColour)
{
	BYTE *scrPntr = startOfScreen_;
	HAPI_TColour col = screenColour;
	for (int i{ 0 }; i < (wWidth_ * wHeight_); i++) {
		memcpy(scrPntr, &col, sizeof(HAPI_TColour));
		scrPntr += sizeof(HAPI_TColour);
	}
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale)
{
	if (shapeWidth > wWidth_ || shapeHeight > wHeight_) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale))", "Error");
		return false;
	}

	BYTE *scrPntr = startOfScreen_;

	int endIncrement = wWidth_ * 4;
	for (int h{ 0 }; h < shapeHeight; h++) {
		memset(scrPntr, grayScale, (sizeof(HAPI_TColour) * shapeWidth));
		scrPntr += endIncrement;
	}
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale)
{
	if ((shapeWidth + posX) > wWidth_ || posX < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale))", "Error");
		return false; 
	}
	else if ((shapeHeight + posY) > wHeight_ || posY < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale))", "Error");
		return false; } // and Y-direction

	int endIncrement = wWidth_ * 4;
	int startByte = (posX + (posY * wWidth_)) * 4;

	BYTE *scrPntr = startOfScreen_;
	scrPntr += startByte; //Sets screen pointer to original writing position

	for (int h{ startByte }; h < (wWidth_ * shapeHeight * 4) + startByte; h += endIncrement) {
		memset(scrPntr, grayScale, (sizeof(HAPI_TColour) * shapeWidth));
		scrPntr += endIncrement;
	}
	return true;
}

bool Graphics::Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour)
{
	if (shapeWidth > wWidth_ || shapeHeight > wHeight_) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour))", "Error");
		return false;
	}

	BYTE *scrPntr = startOfScreen_;
	int endIncrement = (wWidth_ - shapeWidth) * 4;

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
	if ((shapeWidth + posX) > wWidth_ || posX < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour))", "Error");
		return false;
	} 
	else if ((shapeHeight + posY) > wHeight_ || posY < 0) {
		HAPI.UserMessage("Dimensions out of bounds(Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour))", "Error");
		return false;
	}

	int endIncrement = (wWidth_ - shapeWidth) * 4;
	int startByte = (posX + (posY * wWidth_)) * 4;

	BYTE *scrPntr = startOfScreen_;
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

//bool Graphics::Create_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height)
//{
//	if (spriteMap.find(uniqueName) == spriteMap.end()) {
//		Sprite *a = new Sprite(width, height, fileName);
//		if (!a->Init_Texture()) {
//			delete a;
//			return false;
//		}
//		spriteMap[uniqueName] = a;
//		std::cout << spriteMap.at(uniqueName)->Get_Height();
//		return true;
//	}
//	return false;
//}

//bool Graphics::Create_Anim_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height, int fWidth, int fHeight, int numFrames, int animRow)
//{
//	if (spriteMap.find(uniqueName) == spriteMap.end()) {
//		Sprite *a = new Sprite(width, height, fileName, fWidth, fHeight, numFrames, animRow);
//		if (!a->Init_Texture()) {
//			delete a;
//			return false;
//		}
//		spriteMap[uniqueName] = a;
//		std::cout << spriteMap.at(uniqueName)->Get_Height();
//		return true;
//	}
//	return false;
//}

//bool Graphics::Draw_Sprite(const std::string &spriteName, int posX, int posY) const
//{
//	if (spriteMap.find(spriteName) == spriteMap.end()) {
//		return false;
//	}
//	spriteMap.at(spriteName)->Alpha_Blit(startOfScreen, posX, posY, screenRect);
//	return true;
//}

//void Graphics::Change_Anim(int newAnimRow, const std::string &spriteName)
//{
//	if (spriteMap.find(spriteName) == spriteMap.end()) {
//		HAPI.UserMessage("Sprite not found", "Error");
//		return;
//	}
//	if (!spriteMap.at(spriteName)->Change_Anim(newAnimRow)) {
//		HAPI.UserMessage("Internal sprite animation error", "Error");
//		return;
//	}
//}
