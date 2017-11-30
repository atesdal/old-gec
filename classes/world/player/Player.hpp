#pragma once

#include "..\..\utils\Vector2.hpp"

class Player
{
public:
	Player();
	~Player();

	void Update();
	Util::Vector2 Get_Cam_Pos() const { return camPos_; }
	void Reset_CamPos() { camPos_ = Util::Vector2(0, 0); }
private:
	Util::Vector2 camPos_;
};