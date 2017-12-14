#pragma once

#include "..\..\utils\Vector2.hpp"
#include <string>

namespace GFX {
	class Graphics;
}
namespace Util{
	class Camera;
}

namespace MAP
{
	class Feature;
	class Resource;

	class Tile
	{
	public:
		Tile(std::string spriteKey, int foodYield, int prodYield);
		~Tile();

		void Update();
		void Render(GFX::Graphics *gfx, Util::Camera *pCamera, const int screenWidth, const int screenHeight) const;
		void Set_Pos(Util::Vector2 newPos) { pos_ = newPos; }
		void Move(Util::Vector2 moveVec) { pos_ = pos_ + moveVec; }
		Util::Vector2 Get_Pos() const { return pos_; }
		bool Add_Feature(Feature *feature);
		bool Delete_Feature();
		bool Add_Resource(Resource *resource);
		bool Delete_Resource();
		int Get_F_Yield() const { return food_; }
		int Get_P_Yield() const { return prod_; }

	private:
		std::string spriteKey_;
		Util::Vector2 pos_;
		int food_, prod_;
		bool isImproved_;
		Feature *feature_;
		Resource *resource_;
	};
}
