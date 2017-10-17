#pragma once

#include <HAPI_lib.h>
using namespace HAPISPACE;

class Graphics
{
	public:
		Graphics(int windowWidth, int windowHeight, BYTE *screenPointer);
		~Graphics();

		void Clear_Screen(int grayScale);
		void Clear_Screen(int r, int g, int b);
		bool Draw_Pixel(int shapeWidth, int shapeHeight, int grayScale);
		bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, int grayScale);
		bool Draw_Pixel(int shapeWidth, int shapeHeight, HAPI_TColour shapeColour);
		bool Draw_Pixel(int shapeWidth, int shapeHeight, int posX, int posY, HAPI_TColour shapeColour);
	protected:

	private:
		int wWidth, wHeight;
		BYTE *startOfScreen;
};