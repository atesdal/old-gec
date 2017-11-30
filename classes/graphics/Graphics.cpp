#include "Graphics.hpp"
#include "sprite\Sprite.hpp"
#include "sprite\StaticSprite.hpp"
#include "sprite\LineSprite.hpp"
#include "sprite\SquareSprite.hpp"
#include "..\utils\Rectangle.hpp"
#include "..\utils\Utilities.hpp"
#include "..\utils\Vector2.hpp"
#include <cassert>

namespace GFX
{
	Graphics::Graphics() :
		startOfScreen_(nullptr), screenRect_(nullptr)
	{
		screenRect_ = new Util::Rectangle(0, 0);
	}

	Graphics::~Graphics()
	{
		delete screenRect_;
		for (auto p : spriteMap_) {
			delete p.second;
		}
	}

	void Graphics::Init_Graphics(int screenWidth, int screenHeight, BYTE* screenPtr)
	{
		assert(screenPtr != nullptr);
		wWidth_ = screenWidth;
		wHeight_ = screenHeight;
		startOfScreen_ = screenPtr;
		screenRect_->Set_Width(screenWidth);
		screenRect_->Set_Height(screenHeight);
	}

	void Graphics::Clear_Screen(int grayScale)
	{
		if (grayScale < 0 || grayScale > 255) {
			std::cout << "Clear_Screen(grayScale) out of bounds, check values!" << std::endl;
		}
		memset(startOfScreen_, Util::Max(0, Util::Min(255, grayScale)), (wWidth_ * wHeight_ * 4));
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
			return false;
		} // and Y-direction

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

	bool Graphics::Create_Static_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height)
	{
		if (spriteMap_.find(uniqueName) == spriteMap_.end()) {
			StaticSprite *a = new StaticSprite(width, height, fileName);
			if (!a->Init_Texture()) {
				delete a;
				return false;
			}
			spriteMap_[uniqueName] = a;
			return true;
		}
		return false;
	}

	bool Graphics::Create_Anim_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height, int numFrames, int numRows, DWORD frameTimeMS, int numLoops)
	{
		if (spriteMap_.find(uniqueName) == spriteMap_.end()) {
			if (numRows != 1) {
				SquareSprite *a = new SquareSprite(width, height, fileName, numFrames, numRows, frameTimeMS, numLoops);
				if (!a->Init_Texture()) {
					delete a;
					return false;
				}
				spriteMap_[uniqueName] = a;
				return true;
			}
			else {
				LineSprite *a = new LineSprite(width, height, fileName, numFrames, frameTimeMS, numLoops);
				if (!a->Init_Texture()) {
					delete a;
					return false;
				}
				spriteMap_[uniqueName] = a;
				return true;
			}
		}
		return false;
	}

	bool Graphics::Draw_Sprite(const std::string &spriteName, Util::Vector2 pos, bool forceNonAlpha) const
	{
		if (spriteMap_.find(spriteName) == spriteMap_.end()) {
			return false;
		}
		spriteMap_.at(spriteName)->Render(startOfScreen_, screenRect_, int(pos.x), int(pos.y), forceNonAlpha);
		return true;
	}

	bool Graphics::Reset_Sprite_Loop(std::string & spriteName)
	{
		if (spriteMap_.find(spriteName) == spriteMap_.end()) {
			return false;
		}
		spriteMap_.at(spriteName)->Reset_Loop();
		return true;
	}

	bool Graphics::Set_Sprite_Loop(std::string & spriteName, int amount)
	{
		if (spriteMap_.find(spriteName) == spriteMap_.end()) {
			return false;
		}
		spriteMap_.at(spriteName)->Set_Loop(amount);
		return true;
	}
}
