#include "Feature.hpp"

namespace MAP
{
	Feature::Feature(std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield) :
		spriteKey_(spriteKey), fBonus_(foodBonus), pBonus_(prodBonus), harvestYieldF_(harvestFoodYield), harvestYieldP_(harvestProdYield)
	{

	}


	Feature::~Feature()
	{

	}
}
