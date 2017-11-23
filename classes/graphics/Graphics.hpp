#pragma once

#include <HAPI_lib.h>
using namespace HAPISPACE;

#include <unordered_map>
#include "../graphics/rectangle/Rectangle.hpp"
class Sprite;
class SquareSprite;
class LineSprite;
class StaticSprite;

class Graphics
{
public:
	//Creates graphics instance to colour in the main window
	Graphics(int windowWidth, int windowHeight, BYTE *screenPointer);
	//Destructor for graphics class, deletes itself and all sprites loaded using the class instance
	~Graphics();

	//Clear screen to grayscale
	void Clear_Screen(int grayScale);
	//Clear screen to colour using r, g, b values
	void Clear_Screen(HAPI_TColour screenColour);
	//Colours pixel(s) in a square shape (grayscale) determined by width and height in top left corner
	bool Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale);
	//Colours pixel(s) in a square shape (grayscale) determined by width and height at position (x, y)
	bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale);
	//Colours pixel(s) in a square shape (HAPI_TColour) determined by width and height in top left corner
	bool Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour);
	//Colours pixel(s) in a square shape (HAPI_TColour) determined by width and height at position (x, y)
	bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour);
	//Load non-animated sprite to unordered map with key = uniqueName
	bool Create_Static_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height);
	//Load sprite and adds to unordered map with key = uniqueName, change between line and square sheet layout by adding numRows parameter at the end
	bool Create_Anim_Sprite(const std::string &fileName, const std::string &uniqueName, int width, int height, int fWidth, int fHeight, int numFrames, int numRows = 1);
	//Draw loaded sprite using its key
	bool Draw_Sprite(const std::string &spriteName, int posX, int posY) const;

protected:

private:
	const int wWidth_, wHeight_;
	BYTE *startOfScreen_;
	std::unordered_map<std::string, Sprite*> spriteMap_;
	Rectangle screenRect_;
};
