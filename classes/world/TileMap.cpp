#include "TileMap.hpp"
#include "Tile.hpp"


TileMap::TileMap()
{
}


TileMap::~TileMap()
{
	for (auto p : tileMap_) {
		delete p.second;
	}

	for (auto p : tileVector_) {
		delete p;
	}
}

void TileMap::Update()
{
}

void TileMap::Render(GFX::Graphics *gfx)
{

}

//Tile *grass = new Tile(2, 0);
//Tile *plains = new Tile(1, 1);
//
//grass->Set_Sprite("grassTerrain");
//plains->Set_Sprite("grassTerrain");
//
//tileMap_["grass"] = grass;
//tileMap_["plains"] = plains;
//
//for (int i{ 0 }; i < 5; i++) {
//	for (int w{ 0 }; w < 5; w++) {
//		Tile *a = new Tile((*tileMap_.at("grass")));
//		a->Move_Entity(Util::Vector2(float(tileSize * w), float(tileSize * i)));
//		tileVector_.push_back(a);
//	}
//}


//g_->Create_Static_Sprite("Data\\terrain\\grass.jpg", "grassTerrain", 256, 256);

//Util::Vector2 pos;
//for (auto p : tileVector_) {
//	pos = p->Get_Pos();
//	//The text needs to be checked to see whether it is in view or not, or massive performance hit happens, beware magic numbers
//	if ((int(pos.x) >= 0 && int(pos.y) >= 0) && (int(pos.x) < 1500 && int(pos.y) < 750)) {
//		HAPI.RenderText(int(pos.x + 6), int(pos.y + 5), HAPI_TColour::WHITE, Util::To_String(p->Get_F_Yield()));
//		HAPI.RenderText(int(pos.x + 5), int(pos.y + 15), HAPI_TColour::WHITE, Util::To_String(p->Get_P_Yield()));
//	}
//}