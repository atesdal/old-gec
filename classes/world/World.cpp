#include "World.hpp"
#include "../../classes/graphics/Graphics.hpp"
#include "entity/Entity.hpp"

World::World()
{
	g = new Graphics();
}


World::~World()
{
	delete g;
	for (auto p : entityVector_) {
		delete p;
	}
}

bool World::Init_World(int screenWidth, int screenHeight)
{
	if (!HAPI.Initialise(screenWidth, screenHeight, "Feeling happi")) {
		return false;
	}
	HAPI.ChangeFont("Arial");
	HAPI.SetShowFPS(true);
	BYTE *screen = HAPI.GetScreenPointer();

	g->Init_Graphics(screenWidth, screenHeight, screen);

	g->Create_Static_Sprite("Data\\alphaThing.tga", "player", 64, 64);
	g->Create_Anim_Sprite("Data\\linetest.png", "line", 1536, 256, 6);
	g->Create_Anim_Sprite("Data\\runningcat.png", "square", 1024, 1024, 2, 4);

	for (int i{ 0 }; i < 2; i++) {
		Entity *a = new Entity("line");
		Entity *b = new Entity("square");
		Entity *c = new Entity("player");
		entityVector_.push_back(a);
		entityVector_.push_back(b);
		entityVector_.push_back(c);
	}
	return true;
}

void World::Run()
{
	HAPI_TMouseData mData;
	HAPI_TKeyboardData kData;
	HAPI_TControllerData cData;
	int X, Y;
	X = 98;
	Y = -105;
	
	while (HAPI.Update()) {
		// // // // // // //
		// KEEP THIS HERE //
		// // // // // // //
		g->Clear_Screen(0);
		
		//Patchwork input gathering
		mData = HAPI.GetMouseData();
		kData = HAPI.GetKeyboardData();
		cData = HAPI.GetControllerData(0);

		if (kData.scanCode['S']) {
			Y++;
		}
		else if (kData.scanCode['W']) {
			Y--;
		}
		if (kData.scanCode['D']) {
			X++;
		}
		else if (kData.scanCode['A']) {
			X--;
		}

		
		for (auto p : entityVector_) {
			p->Move_Entity(Vector2(X, Y));
			g->Draw_Sprite(p->Get_Sprite(), p->Get_Pos().x, p->Get_Pos().y);
		}

		// // Controller data
		//if (cData.isAttached) {
		//	if (cData.digitalButtons[HK_DIGITAL_DPAD_DOWN]) {
		//		Y++;
		//		//g.Change_Anim(0, "trump");
		//	}
		//	else if (cData.digitalButtons[HK_DIGITAL_DPAD_UP]) {
		//		Y--;
		//		//g.Change_Anim(2, "trump");
		//	}
		//	if (cData.digitalButtons[HK_DIGITAL_DPAD_LEFT]) {
		//		X--;
		//		//g.Change_Anim(3, "trump");
		//	}
		//	else if (cData.digitalButtons[HK_DIGITAL_DPAD_RIGHT]) {
		//		X++;
		//		//g.Change_Anim(1, "trump");
		//	}
		//}

		//if (X < xRange.upper && X > xRange.lower) {
		//	rRumble = 65535;
		//}
		//else {
		//	rRumble = 0;
		//}
		//if (Y < yRange.upper && Y > yRange.lower) {
		//	lRumble = 65535;
		//}
		//else {
		//	lRumble = 0;
		//}

		//HAPI.SetControllerRumble(0, lRumble, rRumble);
	}
}
