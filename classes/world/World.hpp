#pragma once

#include <vector>

class Entity;
class Graphics;

class World
{
public:
	World();
	~World();

private:
	Graphics *g;
	std::vector<Entity*> entityVector_;
};

