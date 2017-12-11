#include "Unit.hpp"
#include "..\..\world\map\Tile.hpp"

SIM::Unit::Unit() :
	Entity()
{
	isClickable_ = true;
}


SIM::Unit::~Unit()
{
}

void SIM::Unit::Update()
{
		
}
	
void SIM::Unit::Move_Entity(MAP::Tile *newPos)
{
	if (newPos == nullptr) {
		return;
	}
	currTile_ = newPos;
	pos_ = currTile_->Get_Pos();
}
