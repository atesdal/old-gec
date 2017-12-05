#pragma once

#include <vector>
#include <unordered_map>

class Tile;
namespace GFX {
	class Graphics;
}

class TileMap
{
public:
	TileMap();
	~TileMap();

	void Update();
	void Render(GFX::Graphics *gfx);

private:
	const int mapWidth_, mapHeight_;
	std::unordered_map<std::string, Tile*> tileMap_;
	std::vector<Tile*> tileVector_;
};

