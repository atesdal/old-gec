#include "Player.hpp"
#include <HAPI_lib.h>

Player::Player() :
	camPos_(Util::Vector2(0, 0))
{

}

Player::~Player()
{

}

void Player::Update()
{
	static const HAPISPACE::HAPI_TKeyboardData &kData = HAPI.GetKeyboardData();

	if (kData.scanCode['W']) {
		camPos_ = camPos_ + Util::Vector2(0, -5);
	}
	else if (kData.scanCode['S']) {
		camPos_ = camPos_ + Util::Vector2(0, 5);
	}
	if (kData.scanCode['A']) {
		camPos_ = camPos_ + Util::Vector2(-5, 0);
	}
	else if (kData.scanCode['D']) {
		camPos_ = camPos_ + Util::Vector2(5, 0);
	}
}
