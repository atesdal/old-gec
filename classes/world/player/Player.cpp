#include "Player.hpp"
#include "..\..\utils\Utilities.hpp"
#include <iostream>

namespace SIM
{
	Player::Player() :
		camPos_(Util::Vector2(0, 0)), worldMPos_(Util::Vector2(0, 0)), 
		mData(HAPI.GetMouseData()), kData(HAPI.GetKeyboardData()), hasClicked_(false), selectedEntIndex_(-1)
	{
		
	}

	Player::~Player()
	{

	}

	void Player::Update()
	{
		
		mData = HAPI.GetMouseData();
		kData = HAPI.GetKeyboardData();
		hasClicked_ = false;

		if (mData.leftButtonDown) {
			Convert_M_To_World();
			hasClicked_ = true;
		}
		else if (mData.rightButtonDown) {
			Convert_M_To_World();
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
	}

	void Player::Select(int indexToSelect)
	{
		selectedEntIndex_ = indexToSelect;
	}

	void Player::Convert_M_To_World()
	{
		worldMPos_ = Util::Vector2(float(mData.x), float(mData.y)) + camPos_;
	}
}
