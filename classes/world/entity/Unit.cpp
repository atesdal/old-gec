#include "Unit.hpp"
#include "..\..\world\map\Tile.hpp"
#include <algorithm>
#include <iostream>

namespace SIM
{
	Unit::Unit() :
		Entity(), totalMoves_(1)
	{
		isClickable_ = true;
		movesLeft_ = 1;
	}


	Unit::~Unit()
	{
	}

	void Unit::Update()
	{
		//std::cout << movesLeft_ << std::endl;
		if (!path_.empty()) {
			Move();
		}
	}

	void Unit::Move_Entity(std::vector<MAP::Tile*> path)
	{
		if (path_.empty()) {
			for (auto p : path) {
				path_.push(p);
			}
		}
		else {
			while (!path_.empty()) {
				path_.pop();
			}
		}
	}


	void Unit::Reset()
	{
		movesLeft_ = totalMoves_;
	}

	void Unit::Move()
	{
		while (movesLeft_ > 0) {
			std::cout << "MOVED" << std::endl;
			currTile_ = path_.top();
			pos_ = currTile_->Get_Pos();
			movesLeft_--;

			path_.pop();
			
			if (movesLeft_ == 0) {
				break;
			}
		}
	}
}
