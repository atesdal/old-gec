#include "Entity.hpp"
#include "..\..\graphics\Graphics.hpp"
#include "..\..\utils\Camera.hpp"
#include "..\..\utils\Rectangle.hpp"
#include <cassert>

namespace SIM
{
	Entity::Entity() :
		spriteKey_(""), pos_(Util::Vector2(0, 0)), isActive_(true), isClickable_(false), side_(Faction::ENeutral), currTile_(nullptr)
	{

	}

	Entity::~Entity()
	{

	}

	void Entity::Render(GFX::Graphics *gfx, Util::Camera *pCamera) const
	{
		float camX = pos_.x + float(pCamera->Get_X());
		float camY = pos_.y + float(pCamera->Get_Y());
		Util::Vector2 renderPos(camX, camY);
		gfx->Draw_Sprite(spriteKey_, renderPos);
	}

	void Entity::Set_Sprite(std::string newSprite, GFX::Graphics *gfx)
	{
		spriteKey_ = newSprite;
		boundRect_ = gfx->Get_Rect(newSprite);
		assert(boundRect_ != nullptr);
	}

	void Entity::Set_Active(bool active)
	{
		isActive_ = active;
	}

	void Entity::Set_Side(Faction side)
	{
		side_ = side;
	}

	bool Entity::Is_Colliding(const Util::Vector2 *other)
	{
		if (boundRect_->Contains(other, int(pos_.x), int(pos_.y))) {
			return true;
		}
		return false;
	}

	bool Entity::Is_Colliding(const Util::Rectangle *other)
	{
		if (!boundRect_->Not_Contained(other, int(pos_.x), int(pos_.y))) {
			return true;
		}
		return false;
	}

	bool Entity::operator==(Entity &other) const
	{
		return (side_ == other.Get_Side()) ? true : false;
	}

	bool Entity::operator!=(Entity &other) const
	{
		return (side_ != other.Get_Side()) ? true : false;
	}
}
