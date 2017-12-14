#pragma once

#include <string>

namespace MAP
{
	class Feature
	{
	public:
		Feature(std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield);
		~Feature();

		std::string Get_Sprite_Key() const { return spriteKey_; }
		int Get_F_Bonus() const { return fBonus_; }
		int Get_P_Bonus() const { return pBonus_; }
		int Get_F_Harvest() const { return harvestYieldF_; }
		int Get_P_Harvest() const { return harvestYieldP_; }
	private:
		const int fBonus_, pBonus_, harvestYieldF_, harvestYieldP_;
		std::string spriteKey_;
	};
}
