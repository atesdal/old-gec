#include "LineSprite.hpp"
#include "..\..\utils\Utilities.hpp"
#include <cassert>

LineSprite::LineSprite(int textureWidth, int textureHeight, std::string path, int frameAmount, DWORD frameTimeMS, int numLoops) :
	Sprite(textureWidth, textureHeight, path), frameNum_(0), numFrames_(frameAmount), numLoops_(numLoops), loopCounter_(0), frameDelay_(frameTimeMS)
{
	frameRect_.Set_Width(textureWidth / numFrames_);
	lastUpdate_ = HAPI.GetTime();
}

LineSprite::~LineSprite()
{
	delete[] tPntr_;
}

void LineSprite::Render(BYTE *screenPtr, const Rectangle &dest, int posX, int posY, bool forceNonAlpha)
{
	assert(screenPtr != nullptr);
	BYTE *scrPtr{ screenPtr };
	BYTE *drawPntr{ tPntr_ };

	Rectangle tRect(frameRect_);

	tRect.Clip_To(dest, posX, posY);

	tRect.Translate(frameRect_.Get_Width() * frameNum_, 0);
	
	//Allows user to prevent function from checking alpha values, use if you know texture does not use alpha channels
	if (forceNonAlpha) {
		if (frameRect_.Not_Contained(dest, posX, posY)) {
			//Do nothing
		}
		else if (frameRect_.Contained_In(dest, posX, posY)) {
			//Screen increment and startbyte based on position
			int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (posX + (posY * dest.Get_Width())) * 4;
			scrPtr += startByte;
			
			//Same as above for texture
			int endIncrementT = (Get_Width() - tRect.Get_Width()) * 4;
			int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * Get_Width())) * 4;
			drawPntr += startByteT;

			for (int h{ 0 }; h < tRect.Get_Height(); h++) {
				for (int w{ 0 }; w < tRect.Get_Width(); w++) {
					memcpy(scrPtr, drawPntr, sizeof(HAPI_TColour));
					scrPtr += sizeof(HAPI_TColour);
					drawPntr += sizeof(HAPI_TColour);
				}
				scrPtr += endIncrement;
				drawPntr += endIncrementT;
			}
		}
		else {
			//Screen increment and startbyte
			int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (Util::Max(0, posX) + (Util::Max(0, posY) * dest.Get_Width())) * 4;
			scrPtr += startByte;

			//Texture increment and startbyte
			int endIncrementT = (Get_Width() - tRect.Get_Width()) * 4;
			int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * Get_Width())) * 4;
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
		if (frameRect_.Not_Contained(dest, posX, posY)) {
			//Do nothing
		}
		else if (frameRect_.Contained_In(dest, posX, posY)) {
			//Screen increment and startbyte based on position
			int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (posX + (posY * dest.Get_Width())) * 4;
			scrPtr += startByte;

			//Same as above for texture
			int endIncrementT = (Get_Width() - tRect.Get_Width()) * 4;
			int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * Get_Width())) * 4;
			drawPntr += startByteT;

			for (int h{ 0 }; h < tRect.Get_Height(); h++) {
				for (int w{ 0 }; w < tRect.Get_Width(); w++) {
					alpha = drawPntr[3];
					if (alpha == 0) {//Invisible
						//Do nothing
					}
					else if (alpha == 255) {//No transparency
						memcpy(scrPtr, drawPntr, (sizeof(HAPI_TColour)));
					}
					else {//Blended alpha
						Alpha_Blit(scrPtr, drawPntr);
					}
					scrPtr += sizeof(HAPI_TColour);
					drawPntr += sizeof(HAPI_TColour);
				}
				scrPtr += endIncrement;
				drawPntr += endIncrementT;
			}
		}
		else {
			//Screen increment and startbyte
			int endIncrement = (dest.Get_Width() - tRect.Get_Width()) * 4;
			int startByte = (Util::Max(0, posX) + (Util::Max(0, posY) * dest.Get_Width())) * 4;
			scrPtr += startByte;

			//Texture increment and startbyte
			int endIncrementT = (Get_Width() - tRect.Get_Width()) * 4;
			int startByteT = (tRect.Get_Left() + (tRect.Get_Top() * Get_Width())) * 4;
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
	if (HAPI.GetTime() - lastUpdate_ >= frameDelay_) {
		if (loopCounter_ <= numLoops_) {
			if (frameNum_ < (numFrames_ - 1)) {
				frameNum_++;
			}
			else {
				frameNum_ = 0;
				if (numLoops_ != 0) {
					loopCounter_++;
				}
			}
		}
		lastUpdate_ = HAPI.GetTime();
	}
}

void LineSprite::Reset_Loop()
{
	loopCounter_ = 0;
}

void LineSprite::Set_Loop(int amount)
{
	assert(amount >= 0);
	numLoops_ = amount;
}
