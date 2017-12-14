#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>

namespace GFX {
	class Graphics;
}
namespace Util {
	class Camera;
	class Rectangle;
}
namespace MAP {
	class Tile;
}

enum class Faction {
	EPlayer,
	EComp,
	ENeutral
};

namespace SIM
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		//Virtuals
		virtual void Update() = 0;
		virtual void Render(GFX::Graphics *gfx, Util::Camera *pCamera) const;
		virtual void Move_Entity(MAP::Tile *newPos) = 0;

		//Base entity functions
		Util::Vector2 Get_Pos() const { return pos_; }
		bool Is_Clickable() const { return isClickable_; }
		void Set_Sprite(std::string newSprite, GFX::Graphics *gfx);
		std::string Get_Sprite() const { return spriteKey_; }
		bool Is_Active() const { return isActive_; }
		void Set_Active(bool active);
		Faction Get_Side() const { return side_; }
		void Set_Side(Faction side);
		Util::Rectangle* Get_Bounds() const { return boundRect_; }

		bool Is_Colliding(const Util::Vector2 *other);
		bool Is_Colliding(const Util::Rectangle *other);
		bool operator==(Entity &other) const;
		bool operator!=(Entity &other) const;

	protected:
		std::string spriteKey_;
		Util::Vector2 pos_;
		bool isActive_, isClickable_;
		Faction side_;
		MAP::Tile *currTile_;
		Util::Rectangle *boundRect_;
	};
}
