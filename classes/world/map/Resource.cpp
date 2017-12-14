#include "Resource.hpp"

MAP::Resource::Resource(std::string spriteKey, int foodBonus, int prodBonus, int harvestFoodYield, int harvestProdYield) :
	spriteKey_(spriteKey), fBonus_(foodBonus), pBonus_(prodBonus), harvestYieldF_(harvestFoodYield), harvestYieldP_(harvestProdYield)
{

}


MAP::Resource::~Resource()
{
}
