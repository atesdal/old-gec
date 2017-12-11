#pragma once

#include <string>

namespace MAP
{
	class Resource
	{
	public:
		Resource(std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield);
		~Resource();

		std::string Get_Sprite_Key() const { return spriteKey_; }
		int Get_F_Bonus() const { return fBonus_; }
		int Get_P_Bonus() const { return pBonus_; }
		int Get_F_Harvest() const { return harvestYieldF_; }
		int Get_P_Harvest() const { return harvestYieldP_; }
		//Add function and var for unique resource granted when improved

	private:
		const int fBonus_, pBonus_, harvestYieldF_, harvestYieldP_;
		std::string spriteKey_;
	};
}
