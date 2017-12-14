#include "World.hpp"
#include "player\Player.hpp"
#include "entity\Entity.hpp"
#include "entity\Unit.hpp"
#include "map\TileMap.hpp"
#include "map\Tile.hpp"
#include "..\graphics\Graphics.hpp"
#include "..\utils\Utilities.hpp"
#include "..\utils\Camera.hpp"
#include "..\utils\Rectangle.hpp"
#include <iostream>

namespace SIM
{
	World::World() :
		g_(nullptr), currPlayer_(0)
	{
		g_ = new GFX::Graphics();
		t_ = new MAP::TileMap(25, 25, 256, 1500, 750);
		c_ = new Util::Camera();
		Player *p = new Player();
		playerVector_.push_back(p);
		c_->Attach_Camera(playerVector_[currPlayer_]);
	}

	World::~World()
	{
		delete g_;
		delete t_;
		delete c_;
		for (auto p : entityVector_) {
			delete p;
		}

		for (auto p : playerVector_) {
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
		g_->Create_Static_Sprite("Data\\background.tga", "background", 256, 256);
		g_->Create_Static_Sprite("Data\\terrain\\grass.jpg", "grass", 256, 256);
		g_->Create_Anim_Sprite("Data\\linetest.png", "line", 1536, 256, 6);
		g_->Create_Anim_Sprite("Data\\runningcat.png", "square", 1024, 1024, 2, 4);

		t_->Create_Tile("grass", "grassTile", 2, 0);
		for (int i{ 0 }; i < 25 * 25; i++) {
			if (!t_->Add_Tile("grassTile")) {
				return false;
			}
		}

		Unit *a = new Unit();
		a->Set_Sprite("player", g_);
		a->Set_Side(Faction::EPlayer);
		a->Move_Entity(t_->Find_Tile(Util::Vector2(300, 400)));
		entityVector_.push_back(a);
		Unit *b = new Unit();
		b->Set_Sprite("player", g_);
		b->Set_Side(Faction::EPlayer);
		b->Move_Entity(t_->Find_Tile(Util::Vector2(0, 0)));
		entityVector_.push_back(b);

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
		//Player update
		playerVector_[currPlayer_]->Update();

		if (playerVector_[currPlayer_]->Has_Ended()) {
			// loop through entities owned by this player and reset their turn-by-turn values to default
			if (currPlayer_ == (playerVector_.size() - 1)) {
				currPlayer_ = 0;
				
			}
			else {
				currPlayer_++;
			}
			std::cout << "Current player is: " << currPlayer_ << std::endl;
		}
		//Camera update
		c_->Update();
		//TileMap update
		t_->Update();
		//Entity update
		for (auto p : entityVector_) {
			p->Update();
		}
		Check_Collosions();

		std::string mPos = Util::To_String(playerVector_[currPlayer_]->Get_M_Pos().x) + ", " + Util::To_String(playerVector_[currPlayer_]->Get_M_Pos().y);

		//Player input
		if (playerVector_[currPlayer_]->Has_Clicked()) {
			HAPI_TMouseData pMouse = playerVector_[currPlayer_]->Get_M_Input();
			HAPI.RenderText(pMouse.x, pMouse.y, HAPI_TColour::WHITE, mPos);
			if (pMouse.leftButtonDown) {
				for (int i{ 0 }; i < int(entityVector_.size()); i++) {
					if (entityVector_[i]->Is_Colliding(&playerVector_[currPlayer_]->Get_M_Pos())) {
						playerVector_[currPlayer_]->Select(i);
						break;
					}
					playerVector_[currPlayer_]->Deselect();
				}
			}
			else if (pMouse.rightButtonDown) {
				int entIndex = playerVector_[currPlayer_]->Get_Selected();
				if (entIndex != -1) {
					entityVector_[entIndex]->Move_Entity(t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos()));
				}
			}
		}
	}

	void World::Render()
	{
		t_->Render(g_, c_);
		for (auto p : entityVector_) {
			if (p->Is_Active()) {
				p->Render(g_, c_);
			}
		}
	}

	void World::Check_Collosions()
	{
		for (size_t i{ 0 }; i < (entityVector_.size() - 1); i++) {
			for (size_t j{ i }; j < (entityVector_.size() - 1); j++) {
				if (entityVector_[i]->Is_Colliding(entityVector_[j]->Get_Bounds())) {
					entityVector_[j]->Set_Active(false);
					std::cout << "C";
				}
			}
		}
	}
}
