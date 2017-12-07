#pragma once

#include "Entity.hpp"

class Unit : public Entity
{
public:
	Unit();
	~Unit();

	void Update() override;
};

