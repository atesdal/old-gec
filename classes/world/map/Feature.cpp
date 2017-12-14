#include "Feature.hpp"

MAP::Feature::Feature(std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield) :
	spriteKey_(spriteKey), fBonus_(foodBonus), pBonus_(prodBonus), harvestYieldF_(harvestFoodYield), harvestYieldP_(harvestProdYield)
{

}


MAP::Feature::~Feature()
{

}
