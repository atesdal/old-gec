#pragma once

#include <HAPI_lib.h>
#include <unordered_map>

using namespace HAPISPACE;

namespace Util {
	class Rectangle;
	class Vector2;
}
class Sprite;
class StaticSprite;
class LineSprite;
class SquareSprite;

namespace GFX
{
	class Graphics
	{
	public:
		//Creates graphics instance to colour in the main window
		Graphics();
		//Destructor for graphics class, deletes itself and all sprites loaded using the class instance
		~Graphics();

		//Initialiser function, to be called from World upon world init
		void Init_Graphics(int screenWidth, int screenHeight, BYTE* screenPtr);
		//Clear screen to grayscale
		void Clear_Screen(int grayScale);
		//Clear screen to colour using r, g, b values
		void Clear_Screen(HAPI_TColour screenColour);
		//[DEPRACATED] Colours pixel(s) in a square shape (grayscale) determined by width and height in top left corner
		bool Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale);
		//[DEPRACATED] Colours pixel(s) in a square shape (grayscale) determined by width and height at position (x, y)
		bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale);
		//[DEPRACATED] Colours pixel(s) in a square shape (HAPI_TColour) determined by width and height in top left corner
		bool Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour);
		//[DEPRACATED] Colours pixel(s) in a square shape (HAPI_TColour) determined by width and height at position (x, y)
		bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour);
		//Load non-animated sprite to unordered map with key = uniqueName
		bool Create_Static_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height);
		//Load sprite and adds to unordered map with key = uniqueName, change between line and square sheet layout by adding numRows parameter at the end
		bool Create_Anim_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height, int numFrames, int numRows = 1, DWORD frameTimeMS = 100, int numLoops = 0);
		//Draw loaded sprite using its key, set forceNonAlpha = true if texture does not use alpha
		bool Draw_Sprite(const std::string &spriteName, Util::Vector2 pos, bool forceNonAlpha = false) const;
		//Resets an animated sprites loop counter
		bool Reset_Sprite_Loop(std::string &spriteName);
		//Sets how many times an animated sprite will loop
		bool Set_Sprite_Loop(std::string &spriteName, int amount);

	protected:

	private:
		int wWidth_, wHeight_;
		BYTE *startOfScreen_;
		std::unordered_map<std::string, Sprite*> spriteMap_;
		Util::Rectangle *screenRect_;
	};
}