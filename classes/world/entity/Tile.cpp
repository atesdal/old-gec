#include "Tile.hpp"
#include "..\..\graphics\Graphics.hpp"

Tile::Tile(int foodYield, int prodYield, Removable *removable, Resource *resource) :
	food_(foodYield), prod_(prodYield), isImproved_(false), rem_(removable), res_(resource)
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

void Tile::Render(GFX::Graphics *gfx)
{
	gfx->Draw_Sprite(spriteKey_, pos_);
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
