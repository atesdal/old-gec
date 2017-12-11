#include "Utilities.hpp"
#include <sstream>

int Util::Max(int v1, int v2)
{
	return (v1 > v2) ? v1 : v2;
}

int Util::Min(int v1, int v2)
{
	return (v1 < v2) ? v1 : v2;
}

float Util::Max(float v1, float v2)
{
	return (v1 > v2) ? v1 : v2;
}

float Util::Min(float v1, float v2)
{
	return (v1 < v2) ? v1 : v2;
}

std::string Util::To_String(int val)
{
	std::ostringstream ss;
	std::string s;
	ss << val;
	s += ss.str();
	return s;
}