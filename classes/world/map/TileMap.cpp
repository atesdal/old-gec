#include "TileMap.hpp"
#include "Tile.hpp"
#include "Feature.hpp"
#include "Resource.hpp"
#include "..\..\utils\Camera.hpp"
#include <queue>
#include <iostream>

namespace MAP
{
	TileMap::TileMap(int mapWidth, int mapHeight, int tileSize, int screenWidth, int screenHeight) :
		mapWidth_(mapWidth), mapHeight_(mapHeight), tileSize_(tileSize), screenWidth_(screenWidth), screenHeight_(screenHeight)
	{

	}

	TileMap::~TileMap()
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

	void TileMap::Update()
	{
		for (auto p : tileVector_) {
			p->Update();
		}
	}

	bool TileMap::Render(GFX::Graphics *gfx, Util::Camera *pCamera) const
	{
		if (gfx == nullptr || pCamera == nullptr) {
			return false;
		}

		for (auto p : tileVector_) {
			p->Render(gfx, pCamera, screenWidth_, screenHeight_);
		}
		return true;
	}

	bool TileMap::Create_Tile(std::string spriteKey, std::string tileName, int foodYield, int prodYield)
	{
		//Checks to see if tile already exists
		//NOTE: you can have several tiles with the same data as long as tileName is unique
		if (tileMap_.find(tileName) == tileMap_.end()) {
			Tile *newTileTemp = new Tile(spriteKey, foodYield, prodYield);
			Create_Feature("feature", "background", 2, 2, 0, 0);
			//newTileTemp->Add_Feature(featMap_.at("feature"));
			tileMap_[tileName] = newTileTemp;
			return true;
		}
		return false;
	}

	bool TileMap::Add_Tile(std::string tileName)
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
				if (tileVector_.size() % mapWidth_ == 0) {//New row
					//Check when cast occurs to avoid float division if possible
					tilePos = Util::Vector2(0.0f, (float(tileVector_.size() / mapHeight_)) * tileSize_);
					int northIndex = tileVector_.size() - mapWidth_;
					//Set north boundary for new tile
					newTile->Set_Bounds(Tile::DIR::NORTH, tileVector_[northIndex]);
					//Update south boundary for north tile to reflect new tile
					tileVector_[northIndex]->Set_Bounds(Tile::DIR::SOUTH, newTile);
				}
				else {//Positioned directly to the right
					Util::Vector2 prevPos = tileVector_[tileVector_.size() - 1]->Get_Pos();
					tilePos = Util::Vector2(prevPos.x + float(tileSize_), prevPos.y);
					if (tileVector_.size() > mapWidth_) {//If multiple rows exist in tileVector_
						//Set boundaries for new tile
						int westIndex = tileVector_.size() - 1;
						newTile->Set_Bounds(Tile::DIR::WEST, tileVector_[westIndex]);
						int northIndex = tileVector_.size() - mapWidth_;
						newTile->Set_Bounds(Tile::DIR::NORTH, tileVector_[northIndex]);
						//Update east boundary for western tile to reflect new tile
						tileVector_[westIndex]->Set_Bounds(Tile::DIR::EAST, newTile);
						//Same as above for northern tile
						tileVector_[northIndex]->Set_Bounds(Tile::DIR::SOUTH, newTile);
					}
					else {//If this is the first row in tileVector_
						//Set boundaries for new tile
						int westIndex = tileVector_.size() - 1;
						newTile->Set_Bounds(Tile::DIR::WEST, tileVector_[westIndex]);
						//Update east boundary for western tile to reflect new tile
						tileVector_[westIndex]->Set_Bounds(Tile::DIR::EAST, newTile);
					}
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

	bool TileMap::Create_Feature(std::string featKey, std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield)
	{
		if (featMap_.find(featKey) == featMap_.end()) {
			Feature *newFeat = new Feature(spriteKey, foodBonus, prodBonus, harvestFoodYield, harvestProdYield);
			featMap_[featKey] = newFeat;
			return true;
		}
		return false;
	}

	bool TileMap::Create_Resource(std::string resKey, std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield)
	{
		if (resMap_.find(resKey) == resMap_.end()) {
			Resource *newRes = new Resource(spriteKey, foodBonus, prodBonus, harvestFoodYield, harvestProdYield);
			resMap_[resKey] = newRes;
			return true;
		}
		return false;
	}

	Tile* MAP::TileMap::Find_Tile(Util::Vector2 pos) const
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

	std::vector<Tile*> TileMap::Find_Path(Tile *start, Tile *end)
	{
		std::vector<Tile*> path, bounds;
		std::queue<Tile*> frontier;
		Tile* current = nullptr;

		frontier.push(start);
		
		while (!frontier.empty()) {
			current = frontier.front();
			frontier.pop();
			current->Set_Visited(true);

			bounds = current->Get_Bounds();
			for (auto p : bounds) {
				if (p != nullptr && !p->Has_Visited()) {
					frontier.push(p);
					p->Set_Visited(true);
					p->Set_Previous(current);
					if (p == end) {
						Fill_Path(p, path);
						while (!frontier.empty()) {
							frontier.pop();
						}
						break;
					}
				}
			}
		}
		for (auto p : tileVector_) {
			p->Set_Previous(nullptr);
			p->Set_Visited(false);
		}
		return path;
	}

	void TileMap::Fill_Path(Tile *target, std::vector<Tile*> &pathVector)
	{
		Tile* current = target;
		while (current->Get_Prev() != nullptr) {
			pathVector.push_back(current);
			current = current->Get_Prev();
		}
	}
}
