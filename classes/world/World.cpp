#include "World.hpp"
#include "player\Player.hpp"
#include "entity\Entity.hpp"
#include "entity\Tile.hpp"
#include "..\graphics\Graphics.hpp"
#include "..\utils\Utilities.hpp"


#include <iostream>

namespace SIM
{
	World::World() :
		g_(nullptr), p_(nullptr)
	{
		g_ = new GFX::Graphics();
		p_ = new Player();
	}

	World::~World()
	{
		delete g_;
		delete p_;
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
		Tile *plains = new Tile(1, 1);

		grass->Set_Sprite("grassTerrain");
		plains->Set_Sprite("grassTerrain");

		tileMap_["grass"] = grass;
		tileMap_["plains"] = plains;

		for (int i{ 0 }; i < 5; i++) {
			for (int w{ 0 }; w < 5; w++) {
				Tile *a = new Tile((*tileMap_.at("grass")));
				a->Move_Entity(Util::Vector2(float(tileSize * w), float(tileSize * i)));
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
		p_->Update();
		Util::Vector2 playerPos = p_->Get_Cam_Pos();

		for (auto p : tileVector_) {
			p->Update();
			if (playerPos != Util::Vector2(0, 0)) {
				p->Move_Entity(Util::Vector2((-playerPos.x), (-playerPos.y)));
			}
		}

		for (auto p : entityVector_) {
			p->Update();
		}

		p_->Reset_CamPos();
	}

	void World::Render()
	{
		Util::Vector2 pos;
		for (auto p : tileVector_) {
			p->Render((*g_));
			pos = p->Get_Pos();
			//The text needs to be checked to see whether it is in view or not, or massive performance hit happens, beware magic numbers
			if ((int(pos.x) >= 0 && int(pos.y) >= 0) && (int(pos.x) < 1500 && int(pos.y) < 750)) {
				HAPI.RenderText(int(pos.x + 6), int(pos.y + 5), HAPI_TColour::WHITE, Util::To_String(p->Get_F_Yield()));
				HAPI.RenderText(int(pos.x + 5), int(pos.y + 15), HAPI_TColour::WHITE, Util::To_String(p->Get_P_Yield()));
			}
		}

		for (auto p : entityVector_) {
			p->Render((*g_));
		}
	}
}
