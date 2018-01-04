#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>
#include <unordered_map>

namespace GFX {
	class Graphics;
}
namespace Util {
	class Camera;
}

namespace MAP {
	class Tile;
	class Feature;
	class Resource;

	class TileMap
	{
	public:
		TileMap(int mapWidth, int mapHeight, int tileSize, int screenWidth, int screenHeight);
		~TileMap();
		//Updates tiles
		void Update();
		//Renders tiles
		bool Render(GFX::Graphics *gfx, Util::Camera *pCamera) const;
		//Adds a Tile template for use with Add_Tile
		bool Create_Tile(std::string spriteKey, std::string tileName, int foodYield, int prodYield);
		//Adds a Tile to the world from template
		bool Add_Tile(std::string tileName);
		//Adds a Feature template, to be added to tiles
		bool Create_Feature(std::string featKey, std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield);
		//Adds a Resource template, to be added to tiles
		bool Create_Resource(std::string resKey, std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield);
		//Returns pointer to the tile at given position, if doesn't exist returns nullptr
		Tile* Find_Tile(Util::Vector2 pos) const;
		std::vector<Tile*> Find_Path(Tile *start, Tile *end);
	private:
		void Fill_Path(Tile *target, std::vector<Tile*> &pathVector);

		const int mapWidth_, mapHeight_, tileSize_, screenWidth_, screenHeight_;
		//Holds active Tile pointers
		std::vector<MAP::Tile*> tileVector_;
		//Holds template tiles 
		std::unordered_map<std::string, Tile*> tileMap_;
		std::unordered_map<std::string, Feature*> featMap_;
		std::unordered_map<std::string, Resource*> resMap_;
	};
}