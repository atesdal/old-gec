#include "Entity.hpp"

Entity::Entity() : pos_(Vector2(0, 0)), spriteKey_("")
{

}

Entity::Entity(Vector2 pos) : pos_(pos), spriteKey_("")
{

}

Entity::Entity(Vector2 pos, std::string spriteKey) : pos_(pos), spriteKey_(spriteKey)
{

}

Entity::Entity(std::string spriteKey) : pos_(Vector2(0, 0)), spriteKey_(spriteKey)
{

}

Entity::~Entity()
{

}

void Entity::Update()
{

}
