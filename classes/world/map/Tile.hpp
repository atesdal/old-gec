#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>

class Removable;
class Resource;
namespace GFX {
	class Graphics;
}

class Tile
{
public:
	Tile(std::string spriteKey, int foodYield, int prodYield, Removable *removable = nullptr, Resource *resource = nullptr);
	~Tile();

	void Update();
	void Render(GFX::Graphics *gfx, const int screenWidth, const int screenHeight) const;
	void Set_Pos(Util::Vector2 newPos) { pos_ = newPos; }
	void Move(Util::Vector2 moveVec) { pos_ = pos_ + moveVec; }
	Util::Vector2 Get_Pos() const { return pos_; }
	bool Add_Removable(Removable *removable);
	bool Delete_Removable();
	bool Add_Resource(Resource *resource);
	bool Delete_Resource();
	int Get_F_Yield() const { return food_; }
	int Get_P_Yield() const { return prod_; }

private:
	std::string spriteKey_;
	Util::Vector2 pos_;
	int food_, prod_;
	bool isImproved_;
	Removable *rem_;
	Resource *res_;
};

