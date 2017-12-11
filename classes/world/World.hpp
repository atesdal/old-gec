#pragma once

#include <vector>
#include <unordered_map>

namespace GFX {
	class Graphics;
}
namespace SIM {
	class Player;
	class Entity;
	class Removable;
	class Resource;
}
namespace MAP {
	class TileMap;
}
namespace Util {
	class Camera;
}

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
		MAP::TileMap *t_;
		Util::Camera *c_;
		SIM::Player *p_;
		std::vector<Entity*> entityVector_;
	};
}
