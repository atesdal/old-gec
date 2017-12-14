#pragma once

#include <vector>
#include <unordered_map>

namespace GFX {
	class Graphics;
}

namespace MAP {
	class TileMap;
}
namespace Util {
	class Camera;
}

namespace SIM
{
	class Player;
	class Entity;
	class Removable;
	class Resource;

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
		void Check_Collosions();
		int currPlayer_;

		GFX::Graphics *g_;
		MAP::TileMap *t_;
		Util::Camera *c_;
		std::vector<Player*> playerVector_;
		std::vector<Entity*> entityVector_;
	};
}
