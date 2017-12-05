#include "Tile.hpp"
#include "..\..\graphics\Graphics.hpp"
#include "..\..\utils\Utilities.hpp"

Tile::Tile(std::string spriteKey, int foodYield, int prodYield, Removable *removable, Resource *resource) :
	spriteKey_(spriteKey), food_(foodYield), prod_(prodYield), isImproved_(false), rem_(removable), res_(resource)
{
	
}


Tile::~Tile()
{

}

void Tile::Update()
{
	if (rem_ != nullptr) {
		//Add yield bonus
	}
	if (res_ != nullptr) {
		//Add yield bonus (if any)
		if (isImproved_) {
			//Add resource to owner
		}
	}
	if (isImproved_) {
		//Add +1 to yields
	}
}

void Tile::Render(GFX::Graphics *gfx) const
{
	gfx->Draw_Sprite(spriteKey_, pos_);
	//Need to check if tile is on screen before rendering text, huge performance hit on large maps
	HAPI.RenderText(int(pos_.x + 6), int(pos_.y + 5), HAPI_TColour::WHITE, Util::To_String(food_));
	HAPI.RenderText(int(pos_.x + 5), int(pos_.y + 15), HAPI_TColour::WHITE, Util::To_String(prod_));

}

bool Tile::Add_Removable(Removable *removable)
{
	return false;
}

bool Tile::Delete_Removable()
{
	if (rem_ == nullptr) {
		return false;
	}
	rem_ = nullptr;
	return true;
}

bool Tile::Add_Resource(Resource *resource)
{
	return false;
}

bool Tile::Delete_Resource()
{
	if (res_ == nullptr) {
		return false;
	}
	res_ = nullptr;
	return true;
}
