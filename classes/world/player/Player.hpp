#pragma once

#include "..\..\utils\Vector2.hpp"
#include <HAPI_lib.h>

namespace SIM
{
	class Player
	{
	public:
		Player();
		~Player();

		void Update();
		//Returns vector with current camera offset, for use with Util::Camera class
		Util::Vector2 Get_Pos() const { return camPos_; }
		//Returns mouse data as defined in HAPI
		HAPISPACE::HAPI_TMouseData Get_M_Input() { return mData; }
		//Returns mouse position in world position
		Util::Vector2 Get_M_Pos() const { return worldMPos_; }
		//Returns keyboard data as defined in HAPI
		HAPISPACE::HAPI_TKeyboardData Get_K_Input() { return kData; }
		//Checks if user has pressed a mouse button
		bool Has_Clicked() const { return hasClicked_; }
		//Selects a selectable entity
		void Select(int indexToSelect);
		//Deselects entity
		void Deselect() { selectedEntIndex_ = -1; }
		//Returns index to selected entity, -1 if none selected
		int Get_Selected() const { return selectedEntIndex_; }
		
		bool Has_Ended() const { return endedTurn_; }

		 
	private:
		//Converts mouse screen position to world position
		void Convert_M_To_World();

		Util::Vector2 camPos_, worldMPos_;
		HAPISPACE::HAPI_TMouseData mData;
		HAPISPACE::HAPI_TKeyboardData kData;
		bool hasClicked_, endedTurn_;
		int selectedEntIndex_;
	};
}
