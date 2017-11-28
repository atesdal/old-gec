#include "Utilities.hpp"

namespace Util
{
	int Max(int v1, int v2)
	{
		return (v1 > v2) ? v1 : v2;
	}

	int Min(int v1, int v2)
	{
		return (v1 < v2) ? v1 : v2;
	}

	float Max(float v1, float v2)
	{
		return (v1 > v2) ? v1 : v2;
	}

	float Min(float v1, float v2)
	{
		return (v1 < v2) ? v1 : v2;
	}
}