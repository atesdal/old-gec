#include "TileMap.hpp"
#include "Tile.hpp"
#include "Feature.hpp"
#include "Resource.hpp"
#include "..\..\utils\Camera.hpp"

MAP::TileMap::TileMap(int mapWidth, int mapHeight, int tileSize, int screenWidth, int screenHeight) :
	mapWidth_(mapWidth), mapHeight_(mapHeight), tileSize_(tileSize), screenWidth_(screenWidth), screenHeight_(screenHeight)
{

}

MAP::TileMap::~TileMap()
{
	for (auto p : tileVector_) {
		delete p;
	}

	for (auto p : tileMap_) {
		delete p.second;
	}

	for (auto p : featMap_) {
		delete p.second;
	}

	for (auto p : resMap_) {
		delete p.second;
	}
}

void MAP::TileMap::Update()
{
	for (auto p : tileVector_) {
		p->Update();
	}
}

bool MAP::TileMap::Render(GFX::Graphics *gfx, Util::Camera *pCamera) const
{
	if (gfx == nullptr || pCamera == nullptr) {
		return false;
	}

	for (auto p : tileVector_) {
		p->Render(gfx, pCamera, screenWidth_, screenHeight_);
	}
	return true;
}

bool MAP::TileMap::Create_Tile(std::string spriteKey, std::string tileName, int foodYield, int prodYield)
{
	//Checks to see if tile already exists
	//NOTE: you can have several tiles with the same data as long as tileName is unique
	if (tileMap_.find(tileName) == tileMap_.end()) {
		Tile *newTileTemp = new Tile(spriteKey, foodYield, prodYield);
		tileMap_[tileName] = newTileTemp;
		return true;
	}
	return false;
}

bool MAP::TileMap::Add_Tile(std::string tileName)
{
	//Checks if current map has space for another tiles
	if (tileVector_.size() < (mapWidth_ * mapHeight_)) {
		//Tile copy constructor from tileMap_
		Tile *newTile = new Tile((*tileMap_.at(tileName)));
		//Checks to see if tile has to be placed at origin (if tileVector_ is empty)
		if (tileVector_.size() != 0) {
			//Temporary vector to perform calculations
			Util::Vector2 tilePos;
			//Checks if tile has to be placed on a new row, ensures final tileVector_ conforms to mapWidth_ and mapHeight_
			if (tileVector_.size() % mapWidth_ == 0) {
				//Check when cast occurs to avoid float division if possible
				tilePos = Util::Vector2(0.0f, (float(tileVector_.size() / mapHeight_)) * tileSize_);
			}
			else {
				Util::Vector2 prevPos = tileVector_[tileVector_.size() - 1]->Get_Pos();
				tilePos = Util::Vector2(prevPos.x + float(tileSize_), prevPos.y);
			}
			newTile->Set_Pos(tilePos);
		}
		else {
			newTile->Set_Pos(Util::Vector2(0, 0));
		}
		tileVector_.push_back(newTile);
		return true;
	}
	return false;
}

bool MAP::TileMap::Create_Feature(std::string featKey, std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield)
{
	if (featMap_.find(featKey) == featMap_.end()) {
		Feature *newFeat = new Feature(spriteKey, foodBonus, prodBonus, harvestFoodYield, harvestProdYield);
		featMap_[featKey] = newFeat;
		return true;
	}
	return false;
}

bool MAP::TileMap::Create_Resource(std::string resKey, std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield)
{
	if (resMap_.find(resKey) == resMap_.end()) {
		Resource *newRes = new Resource(spriteKey, foodBonus, prodBonus, harvestFoodYield, harvestProdYield);
		resMap_[resKey] = newRes;
		return true;
	}
	return false;
}

MAP::Tile* MAP::TileMap::Find_Tile(Util::Vector2 pos) const
{
	//Convert tilemap dimensions into a world coordinate vector
	Util::Vector2 compVector = Util::Vector2(mapWidth_ * float(tileSize_), mapHeight_ * float(tileSize_));

	//Checks to see if input vector is within bounds of tilemap
	if (pos >= compVector) {
		return nullptr;
	}
	if (pos < Util::Vector2(0.0f, 0.0f)) {
		return nullptr;
	}
	//Convert input position to tile-size with integer division
	int modX = int(pos.x) / tileSize_;
	int modY = int(pos.y) / tileSize_;

	//Final calculation to determine the Tile's index in tileVector_
	int vectorIndex = modX + (modY * mapWidth_);

	return tileVector_[vectorIndex];
}
