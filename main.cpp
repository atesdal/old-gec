#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file

	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there are two batch files for creating a redistributable Demo folder
*/
// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "classes\graphics\Graphics.h"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

struct Star {
	float X, Y, Z;
};

void Find_Pixels(int width, int height, int orgWidth, int orgHeight, int posX, int posY, BYTE *screenptr, int R, int G, int B);
void Clear_to_colour(BYTE *scrPntr, int width, int height, int R, int G, int B);
void Init_Stars(Star *sArr, int size, int width, int height);
void Render_Stars(Star *sArr, int size, int width, int height, float speedScale, BYTE *scrPntr);

void HAPI_Main()
{
	const int size{ 10000 }; //Amount of stars
	int width{ 800 }; //Window width
	int height{ 600 }; //Window height
	const HAPI_TMouseData &mData = HAPI.GetMouseData(); //HAPI mouse data
	if (size < 0) { return; } //Exits if there are no stars
	//Star *starArray = new Star[size]; //Creates heap array of star structs, delete at the end of main
	float speed = 0.1f; //Speed modifier

	//Init_Stars(starArray, size, width, height);
	
	HAPI.ChangeFont("Arial");

	if (!HAPI.Initialise(width, height, "Feeling happi")) {
		return;
	}

	BYTE *screen = HAPI.GetScreenPointer();

	Graphics g(width, height, screen);

	HAPI.SetShowFPS(true);

	HAPI_TColour col = HAPI_TColour(200, 0, 0);

	while (HAPI.Update()) {

		g.Draw_Pixel(50, 50, col);

		//Clear_to_colour(screen, 800, 600, 200, 0, 0);

		//g.Clear_Screen(100);
		/*if (mData.leftButtonDown) {
			speed += 0.1f;
		}
		else if (mData.rightButtonDown) {
			speed -= 0.1f;
		}

		Clear_to_colour(screen, width, height, 0, 0, 0);
		Render_Stars(starArray, size, width, height, speed, screen);
		*/
	}
	//delete[] starArray;
}

void Find_Pixels(int width, int height, int orgWidth, int orgHeight, int posX, int posY, BYTE *screenptr, int R, int G, int B)
{
	// Using memcpy and pointer arithmetic, slighly lower FPS in release
	int endOfLineInc = (orgWidth - width) * 4;

	HAPI_TColour col = HAPI_TColour(R, G, B, 0);

	// Simpler algorithm if colour is drawn in position (0, 0)
	if (posX == 0 && posY == 0) {
		for (int h{ 0 }; h < height; h++) {
			for (int w{ 0 }; w < width; w++) {
				memcpy(screenptr, &col, sizeof(HAPI_TColour));
				screenptr += sizeof(HAPI_TColour);
			}
			screenptr += endOfLineInc;
		}
	}
	else {
		if ((width + posX) >= (orgWidth - 1) || posX < 0) { return; } //Checks that pixels can be drawn in X-direction
		else if ((height + posY) >= (orgHeight - 1) || posY < 0) { return; } // and Y-direction

		int startBYTE = (posX + (posY * orgWidth)) * 4; //Finds start bit to write to 

		screenptr += startBYTE; //Sets pointer to starting byte

		for (int h{ startBYTE }; h < (orgWidth * height * 4) + startBYTE; h += endOfLineInc) {
			for (int w{ 0 }; w < (width); w++) {
				memcpy(screenptr, &col, sizeof(HAPI_TColour));
				screenptr += sizeof(HAPI_TColour);
			}
			screenptr += endOfLineInc;
		}
	}

	//// Using direct modification of bits, seemingly small increase in FPS in release
	//int endOfLineInc = orgWidth * 4;
	//
	//if (posX == 0 && posY == 0) {
	//	for (int h{ 0 }; h < (orgWidth * height * 4); h += endOfLineInc) {
	//		for (int w{ 0 }; w < (width * 4); w += 4) {
	//			screenptr[h + w] = 255;
	//			screenptr[h + w + 1] = 255;
	//			screenptr[h + w + 2] = 255;
	//		}
	//	}
	//}
	//else {
	//	int startBYTE = (posX + (posY * orgWidth)) * 4; //Finds start bit to write to 

	//	if ((width + posX) > orgWidth || posX < 0) { return; } //Checks that pixels can be drawn in X-direction
	//	else if ((height + posY) > orgHeight || posY < 0) { return; } // and Y-direction

	//	for (int h{ startBYTE }; h < (orgWidth * height * 4) + startBYTE; h += endOfLineInc) {
	//		for (int w{ 0 }; w < (width * 4); w += 4) {
	//			screenptr[h + w] = 255;
	//			screenptr[h + w + 1] = 255;
	//			screenptr[h + w + 2] = 255;
	//		}
	//	}
	//}
}

void Clear_to_colour(BYTE *scrPntr, int width, int height, int R, int G, int B)
{
	// Clearing screen to colour with memcpy and pointer arithmetic, massive performance increase in release
	HAPI_TColour col = HAPI_TColour(R, G, B, 0);

	for (int h{ 0 }; h < (width * height); h++) {
		memcpy(scrPntr, &col, (sizeof(HAPI_TColour)));
		scrPntr += (sizeof(HAPI_TColour));
	}

	//// Clearing screen to colour using direct modification, much slower than memcpy in release
	//for (int h{ 0 }; h < (height * 4); h += 4) {
	//	for (int w{ 0 }; w < (width * 4); w += 4) {
	//		scrPntr[(h * width) + w] = R;
	//		scrPntr[(h * width) + w + 1] = G;
	//		scrPntr[(h * width) + w + 2] = B;
	//	}
	//}
}

void Init_Stars(Star *sArr, int size, int width, int height)
{
	for (int i{ 0 }; i < size; i++) {
		sArr[i].X = float(rand() % width);
		sArr[i].Y = float(rand() % height);
		sArr[i].Z = float(rand() % 1000);
	}
}

void Render_Stars(Star *sArr, int size, int width, int height, float speedScale, BYTE *scrPntr)
{
	// Vars for scaling on distance, can probably be done better
	float mod;
	float sizeScale;
	float scaledSize;

	// Projection vars
	int Cx = width / 2;
	int Cy = height / 2;
	const int eyeDist{ 150 };

	for (int i{ 0 }; i < size; i++) {
		// Projection calculation
		int Sx = (int)((eyeDist * (sArr[i].X - Cx)) / (sArr[i].Z + eyeDist)) + Cx;
		int Sy = (int)((eyeDist * (sArr[i].Y - Cy)) / (sArr[i].Z + eyeDist)) + Cy;

		// Speed
		sArr[i].Z -= speedScale;

		// Prevents any stars from going behind the 'camera'
		if (sArr[i].Z < 1) {
			sArr[i].Z = float(rand() % 800);
		}

		// Scales size based on distance
		mod = sArr[i].Z / 800;
		sizeScale = 3 * (1 - mod);
		scaledSize = 2 * sizeScale;

		// Colours pixels using info from above calculations
		Find_Pixels(scaledSize, scaledSize, width, height, Sx, Sy, scrPntr, 255, 0, 0);
	}
}