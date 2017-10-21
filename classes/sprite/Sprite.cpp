#include "Sprite.h"
#include <algorithm>

Sprite::Sprite(int textureWidth, int textureHeight, std::string path) :
	tWidth(textureWidth), tHeight(textureHeight), tPath(path), tPntr(nullptr)
{

}

Sprite::~Sprite()
{
	delete[] tPntr;
}

bool Sprite::Init_Texture()
{
	if (!HAPI.LoadTexture(tPath, &tPntr, tWidth, tHeight)) {
		return false;
	}
	return true;
}

bool Sprite::Fast_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest)
{	
	BYTE *scrPntr{ screenPointer };
	BYTE *drawPntr{ tPntr };

	Rectangle tRect(tWidth, tHeight);

	tRect.Clip_To(dest, posX, posY);

	if (tRect.Not_Contained(dest, posX, posY)) {
		//Do nothing
	}
	else if (tRect.Contained_In(dest, posX, posY)) {
		int endIncrement = (dest.Get_Width() * 4);

		int startByte = (posX + (posY * dest.Get_Width())) * 4;
		scrPntr += startByte;

		for (int h{ 0 }; h < tRect.Get_Height(); h++) {
			memcpy(scrPntr, drawPntr, (sizeof(BYTE) * tRect.Get_Width()) * 4);
			scrPntr += endIncrement;
			drawPntr += sizeof(BYTE) * tRect.Get_Width() * 4;
			
		}
	}
	else {
		//int endIncrementS = (screenWidth - (tWidth - 1) * 4; //Used for conditional method
		int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4; //Used for double for loop method
		int startByte = (std::max(0, posX) + (std::max(0, posY) * dest.Get_Width())) * 4;

		int endIncrementT = (tWidth - tRect.Get_Width()) * 4;
		int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * tWidth)) * 4;

		scrPntr += startByte;
		drawPntr += startByteT;

		// Same as above except double for loops being used instead of conditionals
		for (int h{ 0 }; h < tRect.Get_Height(); h++) {
			for (int w{ 0 }; w < tRect.Get_Width(); w++) {
				memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
				scrPntr += sizeof(HAPI_TColour);
				drawPntr += sizeof(HAPI_TColour);
			}
			scrPntr += endIncrement;
			drawPntr += endIncrementT;
		}

		// Draw texture using a single for loop and a conditional to skip lines, seemingly less
		// efficient than just using double for loops
		//for (int h{ startByte }; h < (tHeight * tWidth) + startByte; h++) {
		//	memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
		//	if ((h - startByte + 1) % tWidth == 0) {
		//		scrPntr += endIncrementS;
		//	}
		//	else {
		//		scrPntr += sizeof(HAPI_TColour);
		//	}
		//	drawPntr += sizeof(HAPI_TColour);
		//}
	}
	return true;
}

bool Sprite::Alpha_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest)
{
	BYTE *scrPntr{ screenPointer };
	BYTE *drawPntr{ tPntr };

	Rectangle tRect(tWidth, tHeight);

	tRect.Clip_To(dest, posX, posY);

	if (tRect.Not_Contained(dest, posX, posY)) {
		//Do nothing
	}
	else if (tRect.Contained_In(dest, posX, posY)) {
		int endIncrement = (dest.Get_Width() - tWidth) * 4;

		int startByte = (posX + (posY * dest.Get_Width())) * 4;
		BYTE alpha;
		scrPntr += startByte;

		for (int h{ 0 }; h < tHeight; h++) {
			for (int w{ 0 }; w < tWidth; w++) {
				alpha = drawPntr[3];
				if (alpha == 255) {
					memcpy(scrPntr, drawPntr, sizeof(BYTE));
				}
				else if (alpha == 0) {
					// Do nothing
				}
				else {
					scrPntr[0] += ((alpha * (drawPntr[2] - scrPntr[2])) >> 8);
					scrPntr[1] += ((alpha * (drawPntr[1] - scrPntr[1])) >> 8);
					scrPntr[2] += ((alpha * (drawPntr[0] - scrPntr[0])) >> 8);
				}
				scrPntr += sizeof(BYTE) * 4;
				drawPntr += sizeof(BYTE) * 4;
			}
			scrPntr += endIncrement;
		}
	}
	else {
		int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
		int startByte = (std::max(0, posX) + (std::max(0, posY) * dest.Get_Width())) * 4;

		int endIncrementT = (tWidth - tRect.Get_Width()) * 4;
		int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * tWidth)) * 4;

		BYTE alpha;
		scrPntr += startByte;
		drawPntr += startByteT;

		for (int h{ 0 }; h < tRect.Get_Height(); h++) {
			for (int w{ 0 }; w < tRect.Get_Width(); w++) {
				alpha = drawPntr[3];
				if (alpha == 255) {
					memcpy(scrPntr, drawPntr, sizeof(BYTE));
				}
				else if (alpha == 0) {
					// Do nothing
				}
				else {
					scrPntr[0] += ((alpha * (drawPntr[2] - scrPntr[2])) >> 8);
					scrPntr[1] += ((alpha * (drawPntr[1] - scrPntr[1])) >> 8);
					scrPntr[2] += ((alpha * (drawPntr[0] - scrPntr[0])) >> 8);
				}
				scrPntr += sizeof(BYTE) * 4;
				drawPntr += sizeof(BYTE) * 4;
			}
			scrPntr += endIncrement;
			drawPntr += endIncrementT;
		}
	}
	return true;
}
