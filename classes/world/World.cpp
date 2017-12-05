#include "World.hpp"
#include "player\Player.hpp"
#include "entity\Entity.hpp"
#include "map\TileMap.hpp"
#include "..\graphics\Graphics.hpp"
#include "..\utils\Utilities.hpp"


#include <iostream>

namespace SIM
{
	World::World() :
		g_(nullptr), p_(nullptr)
	{
		g_ = new GFX::Graphics();
		t_ = new SIM::TileMap(3, 3, 256);
		p_ = new Player();
	}
	
	World::~World()
	{
		delete g_;
		delete t_;
		delete p_;
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

		g_->Init_Graphics(screenWidth, screenHeight, screen);		

		if (!LoadLevel()) {
			return false;
		}

		return true;
	}

	bool World::LoadLevel()
	{
		g_->Create_Static_Sprite("Data\\alphaThing.tga", "player", 64, 64);
		g_->Create_Static_Sprite("Data\\terrain\\grass.jpg", "grass", 256, 256);
		g_->Create_Anim_Sprite("Data\\linetest.png", "line", 1536, 256, 6);
		g_->Create_Anim_Sprite("Data\\runningcat.png", "square", 1024, 1024, 2, 4);

		t_->Add_Tile_Template("grass", "grassTile", 2, 0);
		for (int i{ 0 }; i < 9; i++) {
			if (!t_->Add_Tile("grassTile")) {
				return false;
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
		t_->Update();

		for (auto p : entityVector_) {
			p->Update();
		}

		p_->Update();
		Util::Vector2 playerPos = p_->Get_Cam_Pos();
		if (playerPos != Util::Vector2(0.0f, 0.0f)) {
			t_->Move_Relative_To(playerPos);
		}
		p_->Reset_CamPos();
	}

	void World::Render()
	{
		for (auto p : entityVector_) {
			p->Render((*g_));
		}
		t_->Render(g_);
	}
}
