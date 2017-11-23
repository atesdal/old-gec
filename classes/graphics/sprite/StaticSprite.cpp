#include "StaticSprite.hpp"

StaticSprite::StaticSprite(int textureWidth, int textureHeight, std::string path) : Sprite(textureWidth, textureHeight, path)
{

}

StaticSprite::~StaticSprite()
{
	delete[] tPntr_;
}

void StaticSprite::Update(BYTE *screenPtr, const Rectangle &dest, int posX, int posY)
{
	if (screenPtr == nullptr) {
		HAPI.UserMessage("Nullptr errror(Fast_Blit)", "Error");
		return;
	}
	BYTE *scrPtr{ screenPtr };
	BYTE *drawPntr{ tPntr_ };

	Rectangle tRect(Get_Width(), Get_Height());

	tRect.Clip_To(dest, posX, posY);

	if (tRect.Not_Contained(dest, posX, posY)) {
		//Do nothing
	}
	else if(tRect.Contained_In(dest, posX, posY)) {

		int endIncrement = (dest.Get_Width() * 4);
		int startByte = (posX + (posY * dest.Get_Width())) * 4;
		scrPtr += startByte;

		for (int h{ 0 }; h < tRect.Get_Height(); h++) {
			for (int w{ 0 }; w < tRect.Get_Width(); w++) {
				if (drawPntr[3] == 255) {
					memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour)));
				}
				else {
					//Alpha_Blit(scrPtr, drawPntr);
				}
				scrPtr += sizeof(HAPI_TColour);
				drawPntr += sizeof(HAPI_TColour);
			}
			scrPtr += endIncrement;
		}
	}
	else {
		//Screen increment and startbyte
		int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
		int startByte = (std::max(0, posX) + (std::max(0, posY) * dest.Get_Width())) * 4;

		//Texture increment and startbyte
		int endIncrementT = (tWidth_ - tRect.Get_Width()) * 4;
		int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * tWidth_)) * 4;

		//Setting initial pointer values
		scrPtr += startByte;
		drawPntr += startByteT;

		for (int h{ 0 }; h < tRect.Get_Height(); h++) {
			for (int w{ 0 }; w < tRect.Get_Width(); w++) {
				if (drawPntr[3] == 255) {
					memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour)));
				}
				else {
					//Alpha_Blit(scrPtr, drawPntr);
				}
				scrPtr += sizeof(HAPI_TColour);
				drawPntr += sizeof(HAPI_TColour);
			}
			scrPtr += endIncrement;
			drawPntr += endIncrementT;
		}
	}
}
