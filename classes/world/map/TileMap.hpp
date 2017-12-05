#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>
#include <unordered_map>

class Tile;
namespace GFX {
	class Graphics;
}

namespace SIM {
	class TileMap
	{
	public:
		TileMap(int mapWidth, int mapHeight, int tileSize);
		~TileMap();
		//Updates tiles
		void Update();
		//Renders tiles
		bool Render(GFX::Graphics *gfx) const;
		void Move_Relative_To(Util::Vector2 camPos);
		//Adds a Tile template for use with Add_Tile
		bool Add_Tile_Template(std::string spriteKey, std::string tileName, int foodYield, int prodYield);
		//Adds a Tile to the world from template
		bool Add_Tile(std::string tileName);
		//Returns pointer to the tile at given position, if doesn't exist returns nullptr
		Tile* Find_Tile(Util::Vector2 pos) const;
	private:
		const int mapWidth_, mapHeight_, tileSize_;
		//Holds active Tile pointers
		std::vector<Tile*> tileVector_;
		//Holds template tiles 
		std::unordered_map<std::string, Tile*> tileMap_;
	};
}