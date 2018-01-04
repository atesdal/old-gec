#pragma once

#include "Entity.hpp"
#include <stack>

namespace SIM
{
	class Unit : public Entity
	{
	public:
		Unit();
		~Unit();

		void Update() override;
		void Move_Entity(std::vector<MAP::Tile*> path) override;
		void Reset() override;

	private:
		void Move();

		std::stack<MAP::Tile*> path_;
		const int totalMoves_;
		int movesLeft_;
	};
}
