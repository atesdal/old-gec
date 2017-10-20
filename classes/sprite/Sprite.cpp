#include "Sprite.h"

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

bool Sprite::Fast_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY)
{
	BYTE *scrPntr{ screenPointer };
	BYTE *drawPntr{ tPntr };
	//int endIncrementS = (screenWidth - (tWidth - 1) * 4; //Used for conditional method
	int endIncrement = (screenWidth - tWidth) * 4; //Used for double for loop method
	int startByte = (posX + (posY * screenWidth)) * 4;

	scrPntr += startByte;

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


	// Same as above except double for loops being used instead of conditionals

	for (int h{ 0 }; h < (tHeight); h++) {
		for (int w{ 0 }; w < (tWidth); w++) {
			memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
			scrPntr += sizeof(HAPI_TColour);
			drawPntr += sizeof(HAPI_TColour);
		}
		scrPntr += endIncrement;
	}
	return true;
}

bool Sprite::Alpha_Blit(BYTE *screenPointer, int screenWidth, int posX, int posY)
{
	BYTE *scrPntr{ screenPointer };
	BYTE *drawPntr{ tPntr };

	int endIncrement = (screenWidth - tWidth) * 4;

	int startByte = (posX + (posY * screenWidth)) * 4;
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
	return true;
}
