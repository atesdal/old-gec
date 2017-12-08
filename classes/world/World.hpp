#pragma once

#include <vector>
#include <unordered_map>

namespace GFX {
	class Graphics;
}
namespace SIM {
	class TileMap;
}
namespace Util {
	class Camera;
}
class Entity;
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
		SIM::TileMap *t_;
		Util::Camera *c_;
		Player *p_;
		std::vector<Entity*> entityVector_;
	};
}
