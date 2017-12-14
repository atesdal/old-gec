#pragma once

#include "Entity.hpp"

namespace SIM
{
	class Unit : public Entity
	{
	public:
		Unit();
		~Unit();

		void Update() override;
		void Move_Entity(MAP::Tile *newPos) override;

	private:
		int movesLeft_;
	};
}
