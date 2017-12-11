#include "Camera.hpp"
#include "..\world\player\Player.hpp"

namespace Util
{
	Camera::Camera() :
		posX_(0), posY_(0), p_(nullptr)
	{

	}

	Camera::~Camera()
	{

	}

	void Util::Camera::Update()
	{
		if (p_ == nullptr) {
			return;
		}
		Util::Vector2 playerPos = p_->Get_Pos();
		posX_ = int(-playerPos.x);
		posY_ = int(-playerPos.y);
	}

	bool Camera::Attach_Camera(SIM::Player *player)
	{
		if (player == nullptr) {
			return false;
		}
		p_ = player;
		return true;
	}

	int Camera::Get_X() const
	{
		return posX_;
	}

	int Camera::Get_Y() const
	{
		return posY_;
	}
}
