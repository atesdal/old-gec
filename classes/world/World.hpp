#pragma once

#include <vector>
#include <unordered_map>

namespace GFX {
	class Graphics;
}
class Entity;
class Tile;
class Removable;
class Resource;
class Player;

namespace SIM
{
	class World
	{
	public:
		World();
		~World();

		bool Init_World(int screenWidth, int screenHeight);
		void Run();

	private:
		void Update();
		void Render();
		bool LoadLevel();

		GFX::Graphics *g_;
		Player *p_;
		std::vector<Entity*> entityVector_;
		std::vector<Tile*> tileVector_;
		std::unordered_map<std::string, Tile*> tileMap_;
		std::unordered_map<std::string, Removable*> removableMap_;
		std::unordered_map<std::string, Resource*> resourceMap_;
	};
}
