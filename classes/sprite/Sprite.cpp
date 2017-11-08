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
		HAPI.UserMessage("Error(Init_Texture)", "Error");
		return false;
	}
	return true;
}

bool Sprite::Fast_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest)
{
	if (screenPointer == nullptr || tPntr == nullptr) {
		HAPI.UserMessage("Nullptr errror(Fast_Blit)", "Error");
		return false;
	}
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
			memcpy(scrPntr, drawPntr, (sizeof(HAPI_TColour) * tRect.Get_Width()));
			scrPntr += endIncrement;
			drawPntr += sizeof(HAPI_TColour) * tRect.Get_Width();
			
		}
	}
	else {
		//Screen increment and startbyte
		int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
		int startByte = (std::max(0, posX) + (std::max(0, posY) * dest.Get_Width())) * 4;

		//Texture increment and startbyte
		int endIncrementT = (tWidth - tRect.Get_Width()) * 4;
		int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * tWidth)) * 4;

		//Setting initial pointer values
		scrPntr += startByte;
		drawPntr += startByteT;

		for (int h{ 0 }; h < tRect.Get_Height(); h++) {
			for (int w{ 0 }; w < tRect.Get_Width(); w++) {
				memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
				scrPntr += sizeof(HAPI_TColour);
				drawPntr += sizeof(HAPI_TColour);
			}
			scrPntr += endIncrement;
			drawPntr += endIncrementT;
		}
	}
	return true;
}

bool Sprite::Alpha_Blit(BYTE *screenPointer, int posX, int posY, const Rectangle &dest)
{
	if (screenPointer == nullptr || tPntr == nullptr) {
		HAPI.UserMessage("Nullptr errror(Alpha_Blit)", "Error");
		return false;
	}
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
					memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
				}
				else if (alpha == 0) {
					// Do nothing
				}
				else {
					scrPntr[0] += ((alpha * (drawPntr[2] - scrPntr[0])) >> 8);
					scrPntr[1] += ((alpha * (drawPntr[1] - scrPntr[1])) >> 8);
					scrPntr[2] += ((alpha * (drawPntr[0] - scrPntr[2])) >> 8);
				}
				scrPntr += sizeof(HAPI_TColour);
				drawPntr += sizeof(HAPI_TColour);
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
					memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
				}
				else if (alpha == 0) {
					// Do nothing
				}
				else {
					scrPntr[0] += ((alpha * (drawPntr[2] - scrPntr[0])) >> 8);
					scrPntr[1] += ((alpha * (drawPntr[1] - scrPntr[1])) >> 8);
					scrPntr[2] += ((alpha * (drawPntr[0] - scrPntr[2])) >> 8);
				}
				scrPntr += sizeof(HAPI_TColour);
				drawPntr += sizeof(HAPI_TColour);
			}
			scrPntr += endIncrement;
			drawPntr += endIncrementT;
		}
	}
	return true;
}
