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

SIM::World::World() :
	g_(nullptr), p_(nullptr)
{
	g_ = new GFX::Graphics();
	t_ = new MAP::TileMap(25, 25, 256, 1500, 750);
	c_ = new Util::Camera();
	p_ = new Player();
	c_->Attach_Camera(p_);
}
	
SIM::World::~World()
{
	delete g_;
	delete t_;
	delete c_;
	delete p_;
	for (auto p : entityVector_) {
		delete p;
	}
}

bool SIM::World::Init_World(int screenWidth, int screenHeight)
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

bool SIM::World::LoadLevel()
{
	g_->Create_Static_Sprite("Data\\alphaThing.tga", "player", 64, 64);
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
	a->Move_Entity(t_->Find_Tile(Util::Vector2(300, 400)));
	entityVector_.push_back(a);

	return true;
}

void SIM::World::Run()
{
	while (HAPI.Update()) {
		g_->Clear_Screen(0);
		Update();
		Render();
	}
}

void SIM::World::Update()
{
	//Player update
	p_->Update();
	//Camera update
	c_->Update();
	//TileMap update
	t_->Update();
	//Entity update
	for (auto p : entityVector_) {
		p->Update();
	}

	std::string mPos = Util::To_String(p_->Get_M_Pos().x) + ", " + Util::To_String(p_->Get_M_Pos().y);

		
	//Player input
	if (p_->Has_Clicked()) {
		HAPI.RenderText(int(p_->Get_M_Pos().x), int(p_->Get_M_Pos().y), HAPI_TColour::WHITE, mPos);
		HAPI_TMouseData pMouse = p_->Get_M_Input();
		if(pMouse.leftButtonDown){
			for (int i{ 0 }; i < int(entityVector_.size()); i++) {
				if (entityVector_[i]->Is_Colliding(&p_->Get_M_Pos())) {
					p_->Select(i);
					break;
				}
				p_->Deselect();
			}
		}
		else if (pMouse.rightButtonDown) {
			int entIndex = p_->Get_Selected();
			if (entIndex != -1) {
				entityVector_[entIndex]->Move_Entity(t_->Find_Tile(p_->Get_M_Pos()));
			}
		}
	}
}

void SIM::World::Render()
{
	t_->Render(g_, c_);
	for (auto p : entityVector_) {
		p->Render(g_, c_);
	}
}
