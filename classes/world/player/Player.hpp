#pragma once

#include "..\..\utils\Vector2.hpp"

class Player
{
public:
	Player();
	~Player();

	void Update();
	Util::Vector2 Get_Cam_Pos() const { return camPos_; }
	void Zero_CamPos() { camPos_ = Util::Vector2(0, 0); }
	Util::Vector2 Get_M_Input() const { return worldMPos_; }
	bool Has_Clicked() const { return hasClicked_; }
private:
	Util::Vector2 camPos_, currOffset_, worldMPos_;
	bool hasClicked_;
};