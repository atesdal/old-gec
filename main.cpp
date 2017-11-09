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

void HAPI_Main()
{
	int width{ 800 }; //Window width
	int height{ 600 }; //Window height
	int X, Y;
	X = 50;
	Y = 50;
	const HAPI_TMouseData &mData = HAPI.GetMouseData(); //HAPI mouse data
	HAPI_TKeyboardData kData;

	HAPI.ChangeFont("Arial");

	if (!HAPI.Initialise(width, height, "Feeling happi")) {
		return;
	}

	BYTE *screen = HAPI.GetScreenPointer();

	Graphics g(width, height, screen);

	if (!g.Create_Sprite("Data\\alphaThing.tga", "playerSprite", 64, 64)) {
		HAPI.UserMessage("Sprite loading failed", "Error");
		return;
	}

	if (!g.Create_Anim_Sprite("Data\\trump_run.png", "trump", 1536, 1024, 256, 256, 6, 1)) {
		return;
	}

	HAPI.SetShowFPS(true);

	while (HAPI.Update()) {

		kData = HAPI.GetKeyboardData();

		if (kData.scanCode['S']) {
			Y++;
			g.Change_Anim(0, "trump");
		}
		else if (kData.scanCode['W']) {
			Y--;
			g.Change_Anim(2, "trump");
		}
		if (kData.scanCode['D']) {
			X++;
			g.Change_Anim(1, "trump");
		}
		else if (kData.scanCode['A']) {
			X--;
			g.Change_Anim(3, "trump");
		}

		g.Clear_Screen(0);
		if (!g.Draw_Sprite("playerSprite", X, Y)) {
			HAPI.UserMessage("Sprite drawing failed", "Error");
			return;
		}
		g.Draw_Sprite("trump", 50, 50);
		g.Draw_Sprite("trump", 150, 150);
		g.Draw_Sprite("trump", 500, 350);
		g.Draw_Sprite("trump", 300, 700);
		g.Draw_Sprite("trump", 1500, 700);
		g.Draw_Sprite("trump", X, Y);

	}
	return;
}
