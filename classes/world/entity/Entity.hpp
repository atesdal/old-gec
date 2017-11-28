#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>

class Entity
{
public:
	Entity();
	Entity(Vector2 pos);
	Entity(Vector2 pos, std::string spriteKey);
	Entity(std::string spriteKey);
	virtual ~Entity();

	Vector2 Get_Pos() const { return pos_; }
	std::string Get_Sprite() const { return spriteKey_; }
	virtual void Move_Entity(Vector2 newPos) { pos_ = newPos; }
	virtual void Update();

protected:
	std::string spriteKey_;
	Vector2 pos_;
};
