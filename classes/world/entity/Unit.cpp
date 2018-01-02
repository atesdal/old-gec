#include "Unit.hpp"
#include "..\..\world\map\Tile.hpp"

namespace SIM
{
	Unit::Unit() :
		Entity(), movesLeft_(2)
	{
		isClickable_ = true;
	}


	Unit::~Unit()
	{
	}

	void Unit::Update()
	{

	}

	void Unit::Move_Entity(MAP::Tile *newPos)
	{
		if (newPos == nullptr) {
			return;
		}
		currTile_ = newPos;
		pos_ = currTile_->Get_Pos();
	}
}
