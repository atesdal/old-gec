#pragma once

#include <HAPI_lib.h>
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
		bool LoadLevel();
		void Update();
		void Render();
		void Player_Input(HAPISPACE::HAPI_TMouseData mouseData, HAPISPACE::HAPI_TKeyboardData keyboardData);
		int EntityClick(int mX, int mY);
		void Check_Collisions();
		bool Check_Collisions(int entityIndex);

		int currPlayer_;
		GFX::Graphics *g_;
		MAP::TileMap *t_;
		Util::Camera *c_;
		std::vector<Player*> playerVector_;
		std::vector<Entity*> entityVector_;
	};
}
