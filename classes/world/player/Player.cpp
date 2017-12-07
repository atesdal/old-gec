#include "Player.hpp"
#include <HAPI_lib.h>
#include "..\..\utils\Utilities.hpp"

Player::Player() :
	camPos_(Util::Vector2(0, 0)), currOffset_(Util::Vector2(0, 0)), worldMPos_(Util::Vector2(0, 0)), hasClicked_(false)
{

}

Player::~Player()
{

}

void Player::Update()
{
	hasClicked_ = false;
	static const HAPISPACE::HAPI_TKeyboardData &kData = HAPI.GetKeyboardData();
	static const HAPISPACE::HAPI_TMouseData &mData = HAPI.GetMouseData();

	if (mData.leftButtonDown) {
		worldMPos_ = Util::Vector2(float(mData.x), float(mData.y)) + currOffset_;
		hasClicked_ = true;
	}

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
	currOffset_ = currOffset_ + camPos_;
}
