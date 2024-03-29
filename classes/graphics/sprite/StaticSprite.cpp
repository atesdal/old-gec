#include "StaticSprite.hpp"
#include "..\..\utils\Rectangle.hpp"
#include "..\..\utils\Utilities.hpp"
#include <cassert>

StaticSprite::StaticSprite(int textureWidth, int textureHeight, std::string path) : 
	Sprite(textureWidth, textureHeight, path)
{
	
}

StaticSprite::~StaticSprite()
{

}

void StaticSprite::Render(BYTE *screenPtr, const Util::Rectangle *dest, int posX, int posY, bool forceNonAlpha)
{
	assert(screenPtr != nullptr);
	assert(frameRect_ != nullptr);

	BYTE *scrPtr{ screenPtr };
	BYTE *drawPntr{ tPntr_ };

	Util::Rectangle tRect(Get_Width(), Get_Height());

	tRect.Clip_To(dest, posX, posY);

	//Allows user to prevent function from checking alpha values, use if you know texture does not use alpha channels
	if (forceNonAlpha) {
		if (tRect.Not_Contained(dest, posX, posY)) {
			//Do nothing
		}
		else if (tRect.Contained_In(dest, posX, posY)) {
			//Screen increment and startbyte based on position
			int endIncrement = dest->Get_Width() * 4;
			int startByte = (posX + (posY * dest->Get_Width())) * 4;
			scrPtr += startByte;

			for (int h{ 0 }; h < tRect.Get_Height(); h++) {
				memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour) * tRect.Get_Width()));
				drawPntr += sizeof(HAPI_TColour) * tRect.Get_Width();
				//Increment screen pointer to next row
				scrPtr += endIncrement;
			}
		}
		else {
			//Screen increment and startbyte
			int endIncrement = (dest->Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (Util::Max(0, posX) + (Util::Max(0, posY) * dest->Get_Width())) * 4;

			//Texture increment and startbyte
			int endIncrementT = (tWidth_ - tRect.Get_Width()) * 4;
			int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * tWidth_)) * 4;

			//Setting initial pointer values
			scrPtr += startByte;
			drawPntr += startByteT;

			for (int h{ 0 }; h < tRect.Get_Height(); h++) {
				for (int w{ 0 }; w < tRect.Get_Width(); w++) {
					memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour)));
					scrPtr += sizeof(HAPI_TColour);
					drawPntr += sizeof(HAPI_TColour);
				}
				scrPtr += endIncrement;
				drawPntr += endIncrementT;
			}
		}
	}
	else {
		BYTE alpha;
		if (tRect.Not_Contained(dest, posX, posY)) {
			//Do nothing
		}
		else if (tRect.Contained_In(dest, posX, posY)) {
			//Screen increment and startbyte based on position
			int endIncrement = (dest->Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (posX + (posY * dest->Get_Width())) * 4;
			scrPtr += startByte;


			for (int h{ 0 }; h < tRect.Get_Height(); h++) {
				for (int w{ 0 }; w < tRect.Get_Width(); w++) {
					alpha = drawPntr[3];//Getting alpha channel to see if alpha blit (or any blit) is needed
					if (alpha == 0) {//Invisible
						//Do nothing
					}
					else if (alpha == 255) {//No transparency
						memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour)));
					}
					else {//Blended alpha
						Alpha_Blit(scrPtr, drawPntr);
					}
					//Increment pointers by one byte
					scrPtr += sizeof(HAPI_TColour);
					drawPntr += sizeof(HAPI_TColour);
				}
				//Increment screen pointer to next row
				scrPtr += endIncrement;
			}
		}
		else {
			//Screen increment and startbyte
			int endIncrement = (dest->Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (Util::Max(0, posX) + (Util::Max(0, posY) * dest->Get_Width())) * 4;

			//Texture increment and startbyte
			int endIncrementT = (tWidth_ - tRect.Get_Width()) * 4;
			int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * tWidth_)) * 4;

			//Setting initial pointer values
			scrPtr += startByte;
			drawPntr += startByteT;

			for (int h{ 0 }; h < tRect.Get_Height(); h++) {
				for (int w{ 0 }; w < tRect.Get_Width(); w++) {
					alpha = drawPntr[3];
					if (alpha == 0) {
						//Do nothing
					}
					else if (alpha == 255) {
						memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour)));
					}
					else {
						Alpha_Blit(scrPtr, drawPntr);
					}
					scrPtr += sizeof(HAPI_TColour);
					drawPntr += sizeof(HAPI_TColour);
				}
				scrPtr += endIncrement;
				drawPntr += endIncrementT;
			}
		}
	}
}
