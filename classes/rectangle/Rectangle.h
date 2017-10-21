#pragma once
#include <iostream>
#include <algorithm>
class Rectangle
{
public:
	//Rectangle constructor with custom locations for all positions
	Rectangle(int leftPos, int rightPos, int topPos, int botPos) : left(leftPos), right(rightPos),
		top(topPos), bottom(botPos)
	{

	}
	//Zero based rectangle constructor taking width and height
	Rectangle(int width, int height) : left(0), right(width), top(0), bottom(height)
	{

	}
	//Rectangle destructor
	~Rectangle()
	{

	}
	//Returns left of rectangle
	int Get_Left() const { return left; }
	//Returns top of rectangle
	int Get_Top() const { return top; }
	//Returns width of rectangle
	int Get_Width() const { return right; }
	//Returns height of rectangle
	int Get_Height() const { return bottom; }

	//Changes this instance of Rectangle to the intersect value of another rectangle
	void ClipTo(const Rectangle &other, int posX, int posY)
	{
		std::cout << "Before min/max" << std::endl << left << " : " << other.left << std::endl
			<< right << " : " << other.right << std::endl
			<< top << " : " << other.top << std::endl
			<< bottom << " : " << other.bottom << std::endl;
		Translate(posX, posY);
		left = std::max(left, other.left);
		right = std::min(right, other.right);
		top = std::max(top, other.top);
		bottom = std::min(bottom, other.bottom);
		std::cout << "After min/max" << std::endl << left << " : " << other.left << std::endl
			<< right << " : " << other.right << std::endl
			<< top << " : " << other.top << std::endl
			<< bottom << " : " << other.bottom << std::endl;
		Translate(-posX, -posY);
		std::cout << "Post translate" << std::endl << left << " : " << other.left << std::endl
			<< right << " : " << other.right << std::endl
			<< top << " : " << other.top << std::endl
			<< bottom << " : " << other.bottom << std::endl;
	}

private:
	void Translate(int dx, int dy)
	{
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}
	int left, right, top, bottom;
};

