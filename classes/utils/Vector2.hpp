#pragma once
#include <cmath>
#include <ostream>

namespace Util
{
	class Vector2
	{
	public:
		Vector2() = default;
		Vector2(float newX, float newY) : x(newX), y(newY) {}

		Vector2 operator+(const Vector2 &rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2 operator-(const Vector2 &rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2 operator*(float rhs) const
		{
			return Vector2(x * rhs, y * rhs);
		}

		Vector2& operator*=(float rhs)
		{
			return Vector2(x * rhs, y * rhs);
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
		{
			return os << vec.x << ", " << vec.y;
		}

		float Length() const
		{
			return sqrt(x * x + y * y);
		}

		float SquaredLength() const
		{
			return x * x + y * y;
		}

		void MakeUnit()
		{
			float len = Length();

			if (len == 0) {
				return;
			}

			x /= len;
			y /= len;
		}

		float Dot(const Vector2& other) const
		{
			return x * other.x + y * other.y;
		}

		float Cross(const Vector2& other) const
		{
			return x * other.y - y * other.x;
		}

		float x, y;
	};
}
