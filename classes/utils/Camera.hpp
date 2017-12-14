#pragma once

namespace SIM {
	class Player;
}

namespace Util
{
	class Vector2;

	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update();
		bool Attach_Camera(SIM::Player *player);

		int Get_X() const;
		int Get_Y() const;

	private:
		int posX_, posY_;
		SIM::Player *p_;
	};
}
