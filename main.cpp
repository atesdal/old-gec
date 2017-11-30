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
#include "classes\world\World.hpp"

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
	//Insert into world to enable rubmle across the middle
	//int midX = width / 2;
	//int midY = height / 2;
	//MidRange xRange;
	//xRange.lower = midX - 100;
	//xRange.upper = midX + 100;
	//MidRange yRange;
	//yRange.lower = midY - 100;
	//yRange.upper = midY + 100;
	//int rRumble{ 0 };
	//int lRumble{ 0 };

	SIM::World w;
	if (!w.Init_World(1500, 600)) {
		return;
	}
	w.Run();

	return;
}
