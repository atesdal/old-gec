#include "Sprite.h"

Sprite::Sprite(int textureWidth, int textureHeight, std::string path)
{
	tWidth = textureWidth;
	tHeight = textureHeight;
	tPath = path;
	tPntr =  nullptr;
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

bool Sprite::Draw_Texture(BYTE *screenPointer, int screenWidth)
{
	int posX{ 400 };
	int posY{ 300 }; // temp position vars

	BYTE *scrPntr{ screenPointer };
	BYTE *drawPntr{ tPntr };
	int endIncrementS = (screenWidth - (tWidth - 1)) * 4;
	int startByte = (posX + (posY * screenWidth)) * 4;

	scrPntr += startByte;
	for (int h{ startByte }; h < (tHeight * tWidth) + startByte; h++) {
		memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
		if ((h - startByte + 1) % tWidth == 0) {
			scrPntr += endIncrementS;
		}
		else {
			scrPntr += sizeof(HAPI_TColour);
		}
		drawPntr += sizeof(HAPI_TColour);
	}

	//for (int h{ 0 }; h < (tHeight); h++) {
	//	for (int w{ 0 }; w < (tWidth); w++) {
	//		memcpy(scrPntr, drawPntr, sizeof(HAPI_TColour));
	//		scrPntr += sizeof(HAPI_TColour);
	//		drawPntr += sizeof(HAPI_TColour);
	//	}
	//	scrPntr += endIncrementS;
	//}
	return true;
}

//if ((shapeWidth + posX) > wWidth || posX < 0) { return false; } //Checks that pixels can be drawn in X-direction
//else if ((shapeHeight + posY) > wHeight || posY < 0) { return false; } // and Y-direction
//
//int endIncrement = (wWidth - (shapeWidth - 1)) * 4;
//
//int startByte = (posX + (posY * wWidth)) * 4;
//
//BYTE *scrPntr = startOfScreen;
//scrPntr += startByte; //Sets screen pointer to original writing position
//
//for (int h{ startByte }; h < (shapeHeight * shapeWidth) + startByte; h++) {
//	memcpy(scrPntr, &shapeColour, sizeof(HAPI_TColour));
//	if ((h - startByte + 1) % shapeWidth == 0) {
//		scrPntr += endIncrement;
//	}
//	else {
//		scrPntr += sizeof(HAPI_TColour);
//	}
//}
//return true;