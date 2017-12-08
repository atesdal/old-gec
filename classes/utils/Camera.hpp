#pragma once

namespace Util {
	class Vector2;
}
class Player;

namespace Util
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update();
		bool Attach_Camera(Player *player);

		int Get_X() const;
		int Get_Y() const;

	private:
		int posX_, posY_;
		Player *p_;
	};
}
