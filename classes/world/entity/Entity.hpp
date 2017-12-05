#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>

namespace GFX {
	class Graphics;
}

enum class Faction {
	EPlayer,
	EComp,
	ENeutral
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	//Virtuals
	virtual void Update() = 0;
	virtual void Render(GFX::Graphics &gfx) const;
	virtual void Move_Entity(Util::Vector2 newPos) { pos_ = pos_ + newPos; }
	
	//Base entity functions
	Util::Vector2 Get_Pos() const { return pos_; }
	void Set_Sprite(std::string newSprite);
	std::string Get_Sprite() const { return spriteKey_; }
	bool Is_Active() const { return isActive_; }
	void Set_Active(bool active);
	Faction Get_Side() const { return side_; }
	void Set_Side(Faction side);
	bool operator==(Entity &other) const;
	bool operator!=(Entity &other) const;

protected:
	std::string spriteKey_;
	Util::Vector2 pos_;
	bool isActive_;
	Faction side_;
};
