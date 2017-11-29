#pragma once

#include "Entity.hpp"

class Removable;
class Resource;

class Tile : public Entity
{
public:
	Tile(int foodYield, int prodYield, Removable *removable = nullptr, Resource *resource = nullptr);
	~Tile();

	void Update() override final;
	bool Add_Removable(Removable *removable);
	bool Delete_Removable();
	bool Add_Resource(Resource *resource);
	bool Delete_Resource();
	int Get_F_Yield() const { return food_; }
	int Get_P_Yield() const { return prod_; }
private:
	int food_, prod_;
	bool isImproved_;
	Removable *rem_;
	Resource *res_;
};

