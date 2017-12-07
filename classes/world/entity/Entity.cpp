#include "Entity.hpp"
#include "..\..\graphics\Graphics.hpp"


Entity::Entity() :
	spriteKey_(""), pos_(Util::Vector2(0, 0)), isActive_(true), side_(Faction::ENeutral)
{

}

Entity::~Entity()
{

}

void Entity::Render(GFX::Graphics &gfx) const
{
	gfx.Draw_Sprite(spriteKey_, pos_);
}

void Entity::Move_Relative_To(Util::Vector2 camPos)
{
	Move_Entity(Util::Vector2((-camPos.x), (-camPos.y)));
}

void Entity::Set_Sprite(std::string newSprite)
{
	spriteKey_ = newSprite;
}

void Entity::Set_Active(bool active)
{
	isActive_ = active;
}

void Entity::Set_Side(Faction side)
{
	side_ = side;
}

bool Entity::operator==(Entity &other) const
{
	return (side_ == other.Get_Side()) ? true : false;
}

bool Entity::operator!=(Entity &other) const
{
	return (side_ != other.Get_Side()) ? true : false;
}
