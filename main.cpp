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
#include "classes\graphics\Graphics.hpp"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

struct MidRange {
	int lower, upper;
};

void HAPI_Main()
{
	int width{ 1500 }; //Window width
	int height{ 750 }; //Window height
	int midX = width / 2;
	int midY = height / 2;
	MidRange xRange;
	xRange.lower = midX - 100;
	xRange.upper = midX + 100;
	MidRange yRange;
	yRange.lower = midY - 100;
	yRange.upper = midY + 100;
	int rRumble{ 0 };
	int lRumble{ 0 };
	int X, Y;
	X = 50;
	Y = 50;
	const HAPI_TMouseData &mData = HAPI.GetMouseData(); //HAPI mouse data
	HAPI_TControllerData cData;
	HAPI_TKeyboardData kData;

	HAPI.ChangeFont("Arial");

	if (!HAPI.Initialise(width, height, "Feeling happi")) {
		return;
	}

	BYTE *screen = HAPI.GetScreenPointer();

	Graphics g(width, height, screen);


	HAPI.SetShowFPS(true);

	while (HAPI.Update()) {

		kData = HAPI.GetKeyboardData();
		cData = HAPI.GetControllerData(0);

		//if (kData.scanCode['S']) {
		//	Y++;
		//	g.Change_Anim(0, "trump");
		//}
		//else if (kData.scanCode['W']) {
		//	Y--;
		//	g.Change_Anim(2, "trump");
		//}
		//if (kData.scanCode['D']) {
		//	X++;
		//	g.Change_Anim(1, "trump");
		//}
		//else if (kData.scanCode['A']) {
		//	X--;
		//	g.Change_Anim(3, "trump");
		//}

		if (cData.isAttached) {
			if (cData.digitalButtons[HK_DIGITAL_DPAD_DOWN]) {
				Y++;
				//g.Change_Anim(0, "trump");
			}
			else if (cData.digitalButtons[HK_DIGITAL_DPAD_UP]) {
				Y--;
				//g.Change_Anim(2, "trump");
			}
			if (cData.digitalButtons[HK_DIGITAL_DPAD_LEFT]) {
				X--;
				//g.Change_Anim(3, "trump");
			}
			else if (cData.digitalButtons[HK_DIGITAL_DPAD_RIGHT]) {
				X++;
				//g.Change_Anim(1, "trump");
			}
		}

		if (X < xRange.upper && X > xRange.lower) {
			rRumble = 65535;
		}
		else {
			rRumble = 0;
		}
		if (Y < yRange.upper && Y > yRange.lower) {
			lRumble = 65535;
		}
		else {
			lRumble = 0;
		}

		HAPI.SetControllerRumble(0, lRumble, rRumble);

		g.Clear_Screen(0);

	}
	return;
}
