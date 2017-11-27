#pragma once

#include <vector>

class Entity;
class Graphics;

class World
{
public:
	World();
	~World();

	bool Init_World(int screenWidth, int screenHeight);
	void Run();


private:
	Graphics *g;
	std::vector<Entity*> entityVector_;
};

