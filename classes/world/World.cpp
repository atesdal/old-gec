#include "World.hpp"
#include "entity\Entity.hpp"
#include "entity\Tile.hpp"
#include "..\utils\Utilities.hpp"

#include <iostream>

World::World()
{
	g_ = new GFX::Graphics();
}


World::~World()
{
	delete g_;
	for (auto p : entityVector_) {
		delete p;
	}
	for (auto p : tileVector_) {
		delete p;
	}
	for (auto p : tileMap_) {
		delete p.second;
	}
	//for (auto p : removableMap_) {
	//	delete p.second;
	//}
	//for (auto p : resourceMap_) {
	//	delete p.second;
	//}
}

bool World::Init_World(int screenWidth, int screenHeight)
{
	if (!HAPI.Initialise(screenWidth, screenHeight, "Feeling happi")) {
		return false;
	}
	HAPI.ChangeFont("Arial");
	HAPI.SetShowFPS(true);
	BYTE *screen = HAPI.GetScreenPointer();

	g_->Init_Graphics(screenWidth, screenHeight, screen);

	LoadLevel();

	return true;
}

bool World::LoadLevel()
{
	g_->Create_Static_Sprite("Data\\alphaThing.tga", "player", 64, 64);
	g_->Create_Static_Sprite("Data\\terrain\\grass.jpg", "grassTerrain", 256, 256);
	g_->Create_Anim_Sprite("Data\\linetest.png", "line", 1536, 256, 6);
	g_->Create_Anim_Sprite("Data\\runningcat.png", "square", 1024, 1024, 2, 4);

	int tileSize{ 256 };

	Tile *grass = new Tile(2, 0);

	grass->Set_Sprite("grassTerrain");

	tileMap_["grass"] = grass;

	for (int i{ 0 }; i < 2; i++) {
		for (int w{ 0 }; w < 2; w++) {
			Tile *a = new Tile((*tileMap_.at("grass")));
			a->Move_Entity(Vector2(float(tileSize * w), float(tileSize * i)));
			tileVector_.push_back(a);
		}
	}

	return true;
}

void World::Run()
{
	while (HAPI.Update()) {

		g_->Clear_Screen(0);
		Update();
		Render();
	}
}

void World::Update()
{
	for (auto p : tileVector_) {
		p->Update();
	}

	for (auto p : entityVector_) {
		p->Update();
	}
}

void World::Render()
{
	for (auto p : tileVector_) {
		p->Render(*g_);
		//The text needs to be checked to see whether it is in view or not, or massive performance hit happens
		HAPI.RenderText(int(p->Get_Pos().x + 6), int(p->Get_Pos().y + 5), HAPI_TColour::WHITE, Util::To_String(p->Get_F_Yield()));
		HAPI.RenderText(int(p->Get_Pos().x + 5), int(p->Get_Pos().y + 15), HAPI_TColour::WHITE, Util::To_String(p->Get_P_Yield()));
	}

	for (auto p : entityVector_) {
		g_->Draw_Sprite(p->Get_Sprite(), p->Get_Pos());
	}
}
