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
		t_ = new MAP::TileMap(3, 3, 256, 1500, 750);
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
		for (int i{ 0 }; i < 3; i++) {
			if (!t_->Add_Tile("grassTile")) {
				return false;
			}
		}
		t_->Create_Tile("grass", "notGrass", 0, 0);
		for (int i{ 0 }; i < 3; i++) {
			if (!t_->Add_Tile("notGrass")) {
				return false;
			}
		}
		t_->Create_Tile("grass", "defGrass", 5, 5);
		for (int i{ 0 }; i < 3; i++) {
			if (!t_->Add_Tile("defGrass")) {
				return false;
			}
		}

		Unit *a = new Unit();
		a->Set_Sprite("player", g_);
		a->Set_Side(0);
		a->Move_Entity(t_->Find_Tile(Util::Vector2(300, 400)));
		entityVector_.push_back(a);
		Unit *b = new Unit();
		b->Set_Sprite("player", g_);
		b->Set_Side(1);
		b->Move_Entity(t_->Find_Tile(Util::Vector2(0, 0)));
		entityVector_.push_back(b);

		return true;
	}

	void World::Player_Input(HAPISPACE::HAPI_TMouseData &mouseData, HAPISPACE::HAPI_TKeyboardData &keyboardData)
	{
		//HAPI.RenderText(pMouse.x, pMouse.y, HAPI_TColour::WHITE, mPos);
		if (mouseData.leftButtonDown) {
			for (int i{ 0 }; i < int(entityVector_.size()); i++) {
				/**
				Long if-statemend that checks:
				If a player clicked on an entity,
				if that entity is on the same side as the player
				and if that entity is clickable
				*/
				if (entityVector_[i]->Is_Colliding(&playerVector_[currPlayer_]->Get_M_Pos())
					&& entityVector_[i]->Get_Side() == currPlayer_
					&& entityVector_[i]->Is_Clickable())
				{
					playerVector_[currPlayer_]->Select(i);
					break;
				}
				else {
					std::cout << "This: " << t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos()) << std::endl;
					std::cout << "North: " << t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos())->Get_Bounds().north << std::endl;
					std::cout << "South: " << t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos())->Get_Bounds().south << std::endl;
					std::cout << "East: " << t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos())->Get_Bounds().east << std::endl;
					std::cout << "West: " << t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos())->Get_Bounds().west << std::endl;
				}
				playerVector_[currPlayer_]->Deselect();
			}
		}
		else if (mouseData.rightButtonDown) {
			int entIndex = playerVector_[currPlayer_]->Get_Selected();
			if (entIndex != -1) {
				entityVector_[entIndex]->Move_Entity(t_->Find_Tile(playerVector_[currPlayer_]->Get_M_Pos()));
				Check_Collisions(entIndex);
			}
		}
	}

	void World::Run()
	{
		while (HAPI.Update()) {
			g_->Clear_Screen(0);
			Update();
			Render();
			/**
			NOTE ON COLLISION CHECKS
			Due to the nature of a turn based tile game, collisions checks only need to happen
			when a player moves a unit, as nothing will move unless told to do so by a player.
			This might have to change once a way of storing a planned path over several turns is
			added, but in the game's current state this is not necessary.
			*/
		}
	}

	void World::Update()
	{
		//Player update
		playerVector_[currPlayer_]->Update();

		if (playerVector_[currPlayer_]->Has_Ended()) {
			// loop through entities owned by this player and reset their turn-by-turn values to default

			//TODO: Reset turn by turn vals, add owned yields to city, etc.

			//If end of playerVector_ has been reached, reset to player 0
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
			if (p->Is_Active()) {
				p->Update();
			}
		}

		//std::string mPos = Util::To_String(playerVector_[currPlayer_]->Get_M_Pos().x) + ", " + Util::To_String(playerVector_[currPlayer_]->Get_M_Pos().y);

		//Player input
		if (playerVector_[currPlayer_]->Has_Clicked()) {
			Player_Input(playerVector_[currPlayer_]->Get_M_Input(), playerVector_[currPlayer_]->Get_K_Input());
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

	void World::Check_Collisions()
	{
		for (size_t i{ 0 }; i < entityVector_.size(); i++) {
			if (!entityVector_[i]->Is_Active()) {
				continue;
			}
			for (size_t j{ i + 1 }; j < entityVector_.size(); j++) {
				if (!entityVector_[j]->Is_Active()) {
					continue;
				}
				if (entityVector_[i]->Is_Colliding(entityVector_[j])) {
					entityVector_[j]->Set_Active(false);
					std::cout << "C";
				}
			}
		}
	}

	bool World::Check_Collisions(int entityIndex)
	{
		for (size_t i{ 0 }; i < entityVector_.size(); i++) {
			if (i == entityIndex) {
				continue;
			}
			if (entityVector_[entityIndex]->Is_Colliding(entityVector_[i])) {
				//change to damage later
				entityVector_[i]->Set_Active(false);
				return true;
			}
		}
		return false;
	}
}
